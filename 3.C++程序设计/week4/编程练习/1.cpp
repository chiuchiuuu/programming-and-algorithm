	void operator=(char *s)
	{
	    char *tmpstr = new char[strlen(s)];
	    strcpy(tmpstr, s);
		char*temp = strtok(tmpstr, "+");
		r = atof(temp);
		temp = strtok(NULL, "i");
		i = atof(temp);
	}