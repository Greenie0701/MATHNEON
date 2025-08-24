// A few macros to check pointers and their address range to make sure there's
// no unwanted overlap between any two of them 

#define MN_CHECK_DstSRC \
    do { \
        if ((void *)dst < (void *)src) { \
            assert((void *)dst + count <= (void *)src); \
        } else if ((void *)dst > (void *)src) { \
            assert((void *)src + count <= (void *)dst); \
        } \
    } while (0)

#define MN_ASSERT_DS MN_CHECK_DstSRC
