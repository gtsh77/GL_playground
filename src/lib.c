extern char * readFile(char *path)
{
	FILE *file = NULL;
	char *p;
	uint64_t size;
	file = fopen(path,"r");
	if(!file)
	{
		printf("can't open: %s",path);
		return NULL;
	}
	fseek(file,0,2);
	size = ftell(file);
	p = (char *)malloc(size);
	rewind(file);
	fread(p,size,1,file);
	fclose(file);
	return p;
}

extern void debugSC(GLuint sIndex)
{
	char log[2048];
	int length = 0;
	glGetShaderInfoLog(sIndex,2048,&length,log);
	printf("%s\n",log);
}

extern uint64_t getCycles(void)
{
	uint64_t lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}