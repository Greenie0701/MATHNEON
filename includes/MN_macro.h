

// A few macros to check pointers and their address range to make sure there's
// no unwanted overlap between any two of them 

#define MN_CHECKPOINTER_DstSrcCst \
   if ( (void *)dst < (void *)src ) \                         
    { assert ( (void *)dst + count <= (void *)src ); } \
   else if ( (void *)dst > (void *)src ) \
    { assert ( (void *)src + count <= (void *)dst ); }

#define MN_CHECKPOINTER_DstSrc MN_CHECKPOINTER_DstSrcCst
