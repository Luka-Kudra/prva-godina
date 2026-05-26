union str {float f; int i; } s={-7.375};
printf("0:%p\n",&s);
printf("1:%x\n",s.i);
printf("2:%p\n",&s.i);
printf("3:%p\n",&s.f);
printf("4:%x\n",sizeof(s));
printf("5:%d\n",s.i>>31);
printf("0:%p\n",s.i&0x7fffffff)>>23);