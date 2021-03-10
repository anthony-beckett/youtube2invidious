/*
 * Copyright 2021 Anthony Beckett
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/


#include <stdio.h>
#include <string.h>


void
convert_link(char orig_link[])
{
	char *instance = "invidious.kavin.rocks";
	int pos;
	int flag = 0;

	for (pos = 0; flag < 2; pos++) {
		switch (orig_link[pos]) {
			case 'e': /* FALLTHROUGH */
			case 'm':
				flag++;
				break;
			case '/':
				flag += (flag > 0);
				break;
			default:
				flag *= (flag >= 2);
				break;
		}
	}
	printf("https://%s/", instance);
	for (NULL; orig_link[pos]; pos++)
		printf("%c", orig_link[pos]);
	puts("");
}


int
main(int argc, char* argv[])
{
	char youtube_link[strlen(argv[1]) + 2];
	
	if (argc < 2 ) {
		puts("Not enough arguments");
		return 1;
	}
	
	snprintf(youtube_link, strlen(argv[1]) + 2, "%s", argv[1]);
	convert_link(youtube_link);
	return 0;
	
}
