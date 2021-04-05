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



/*                             TODO
 * 1. Add a check to make sure input is actually a youtube_link.
 * 2. Add command line parsing.
 * 3. Add the ability to choose the invidious instance.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100


int
error_check(int count, char* arg_1)
{
	int err_num = 0;

	if (count < 2 ) {
		fprintf(stderr, "ERROR: Not enough arguments\n");
		err_num++;
	}

	if (count > 2) {
		fprintf(stderr, "ERROR: Too many arguments\n");
		err_num++;
	}

	if (strlen(arg_1) > BUFFER) {
		fprintf(stderr, "ERROR: Link exceeds %d characters\n", BUFFER);
		err_num++;
	}

	return err_num;
}


void
convert_link(char* final_link, char orig_link[], char* instance)
{
	int   flag         = 0;
	int   pos;
	char  data[BUFFER];

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

	for (int j = 0; orig_link[pos]; pos++) {
		data[j] = orig_link[pos];
		j++;
	}

	snprintf(final_link, BUFFER, "https://%s/%s", instance, data);
}


int
main(int argc, char* argv[])
{
	char* instance     = "invidious.kavin.rocks";
	char  youtube_link[BUFFER];
	char  invidious_link[BUFFER];

	if (error_check(argc, argv[1]))
		return 1;

	snprintf(youtube_link, BUFFER, "%s", argv[1]);

	convert_link(invidious_link, youtube_link, instance);

	printf("%s\n", invidious_link);

	return 0;
}
