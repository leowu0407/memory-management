#include "mm.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NALLOC 1024
typedef long Align;

union header{
    struct{
    	union header *ptr;
    	unsigned size;
    }s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;


static Header *morecore(unsigned nu){
    char *cp, *sbrk(int);
    Header *up;
    
    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    myfree((void *)(up+1));
    return freep;
} 
void *mymalloc(size_t size)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    
    nunits = (size+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { 
    	base.s.ptr = freep = prevp = &base;
    	base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr){
    	if (p->s.size >= nunits) {
    	    if (p->s.size == nunits)
    	    	prevp->s.ptr = p->s.ptr;
    	    else {
    	    	p->s.size -= nunits;
		p += p->s.size;
		p->s.size = nunits;
    	    }
    	    freep = prevp;
	    return (void *)(p+1);
	}
	if (p == freep)
	    if((p = morecore(nunits)) == NULL)
		return NULL;

    }	
}

void myfree(void *ptr)
{
    Header *bp, *p;
    bp = (Header *)ptr - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    	if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
    		break;
    if (bp + bp->s.size == p->s.ptr) {
    	bp->s.size += p->s.ptr->s.size;
	bp->s.ptr = p->s.ptr->s.ptr;
    } else
	bp->s.ptr = p->s.ptr;
	
    if (p + p->s.size == bp) {
    	p->s.size += bp->s.size;
	p->s.ptr = bp->s.ptr;
    } else
	p->s.ptr = bp;
    freep = p;
}

void *myrealloc(void *ptr, size_t size)
{
    void *temp;
    temp=mymalloc(size);
    memcpy(temp,ptr,size);
    myfree(ptr);
    return temp;
}

void *mycalloc(size_t nmemb, size_t size)
{
    void *p;
    int total_size=size*nmemb;
    p=mymalloc(total_size);
    memset(p,0,total_size);
    return p;
}
