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