#include"api.h"
#include"toBase64.h"
#include"fromBase64.h"
//fprintf(output , "%d " , outByte6 );
				/*unsigned char p = 1;
				p<<=(7);
				for(int i = 0; i < 8; ++i){

					if(p & outByte6){
						fprintf(output , "1");
					}else{
						fprintf(output, "0");
					}
					p>>=(1);
				}
				fprintf(output, "\n");*/

int main(int argv , char* argc[]){


	char base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int cmd = selectOptionFromUser(argv , argc);

	switch(cmd)
	{

	case 0: printf("Entry rules"); return 0; break;

	case 1:	toBase64(argc[2] , base64Alphabet); break;
	
	case 2: fromBase64(argc[2] , base64Alphabet);break;

	}



	return 0;
}