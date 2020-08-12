
char *strcpy(char * dst, const char * src) {
    if (!src) {
        return 0;
    }
    int i, j;
    for(i = 0, j = 0; (src[i] & 0xff) !=0; ) {
        dst[j++] = src[i++];
    }
    dst[j] = '\0';
}


int strlen(const char * s) {
    int len = 0;
    if (!s)
        return len;
    for(; (s[len] & 0xff) !=0; len++) ;
    return len;
}