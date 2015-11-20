#include <stdio.h>
#include <string.h>
#include <windows.h>
#define N 30

int main ()
{
	char empty_string[2] = " ";
	char string_from_a_file[63];
	char string_for_parameters[63];
	char procedure[4] = "def";
	char braket[2] = "(";
	char *pointer_in_a_string;
	char dollar_symbol[2] = "$";
	int counter_parameters_for_the_cycle = 0;
	int number_of_parameters = 0;
	int number_of_string_in_the_code = 0;
	int distance_between_parameters = 0;
	int string_number = 0;
	int position_of_the_file_pointer = 0;
	int number_of_procedure = 0;
	int practical_manipulation = 0;
	int string_length = 0;
	float result;

	struct globalnue_parametru 
	{
		char element[10];
	};

	struct globalnue_parametru parametru[N];

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	FILE *Ruby;
	Ruby = fopen("Ruby.txt","rt");
	while (!feof(Ruby))
	{
		fgets(string_from_a_file, 30, Ruby);
		number_of_string_in_the_code++;
	}
	fclose(Ruby);
	
	Ruby = fopen("Ruby.txt","rt");
	//Кол-во обращений к глобальным переменным 
	while (!feof(Ruby))
	{
		fgets(string_from_a_file, 30, Ruby);
		string_length = strlen(string_from_a_file);
		for (int i = 0; i < string_length; i++)
		{
			if ((string_from_a_file[i] == '$') && (string_from_a_file[i+1] != ' '))
			{
				practical_manipulation++;
			}
		}

		pointer_in_a_string = strstr(string_from_a_file, procedure);
		if (pointer_in_a_string != NULL)
		{
			pointer_in_a_string = strstr(string_from_a_file, braket);
			if (pointer_in_a_string != NULL)
			{
				for (int p = pointer_in_a_string-string_from_a_file+2; p < string_length; p++)
				{
					if (string_from_a_file[p] == ',')
					{
						//kolichestvo_parametrov++;
						practical_manipulation--;
					}
				}
				number_of_procedure++;
				//kolichestvo_parametrov++;
				practical_manipulation--;
				
			}
		}
		//kolichestvo_parametrov = 0;
	}
	fclose(Ruby);

	for (int count = 0; count < number_of_string_in_the_code; count++)
	{
		Ruby = fopen("Ruby.txt", "rt");
		for (int povtor = 0; povtor <= string_number; povtor++)
		{
			fgets(string_for_parameters, 30, Ruby);
			string_length = string_length + strlen(string_for_parameters) + 1;
		}
		fclose(Ruby);
		string_length = string_length - strlen(string_for_parameters);
		
		pointer_in_a_string = strstr(string_for_parameters, procedure);
		if (pointer_in_a_string != NULL)
		{
			pointer_in_a_string = strstr(string_for_parameters, braket);
			if (pointer_in_a_string != NULL)
			{
				for (int x = 0; x < 2; x++)
				{
					Ruby = fopen("Ruby.txt", "rt");
					
					if (string_number > 0)
					{
						if (x > 0)
						{						
							position_of_the_file_pointer = position_of_the_file_pointer + distance_between_parameters + 2; 
						}
						else
						{
							position_of_the_file_pointer = string_length + pointer_in_a_string-string_for_parameters+1;
						}
					}
					else
					{
						if (x > 0)
						{
							position_of_the_file_pointer = position_of_the_file_pointer + distance_between_parameters + 2; 
						}
						else
						{
							position_of_the_file_pointer = pointer_in_a_string-string_for_parameters+2;
						}
					}
					 
					fseek(Ruby, position_of_the_file_pointer, SEEK_SET);
					fscanf(Ruby, "%s", string_for_parameters);
					strcpy(parametru[counter_parameters_for_the_cycle].element, string_for_parameters);
					counter_parameters_for_the_cycle++;
					//printf("%s\n", peremennaya_stroka);
					distance_between_parameters = strlen(string_for_parameters) + 2;
				    fclose(Ruby);
				}
				position_of_the_file_pointer = 0;
				distance_between_parameters = 0;
			}
		}
		string_number++;
		string_length = 0;
	}
	//printf("\n");

/*	for (int y = 0; y < counter; y++)
	{
		printf("%s ", parametru[y].element);
	}
	printf("\n");
*/
	number_of_parameters = counter_parameters_for_the_cycle;
	for (int x = 0; x < counter_parameters_for_the_cycle; x++)
	{
		for (int y = x + 1; y < counter_parameters_for_the_cycle; y++)
		{
			if (strcmp(parametru[x].element, parametru[y].element) == 0)
			{
				strcpy(parametru[y].element, empty_string);
				if (strcmp(parametru[x].element, empty_string) != 0)
				{
					number_of_parameters--;
				}
			}
		}
	}
	printf("Количество параметров: %d\n", number_of_parameters);
/*	for (int y = 0; y < counter; y++)
	{
		printf("%s ", parametru[y].element);
		
	}
	printf("\n\n");
*/ 
	result = (double)practical_manipulation/(number_of_procedure * number_of_parameters);

	printf("Количество подпрограмм: %d", number_of_procedure);
	printf("\nКоличество практических обращений к глобальным переменным: %d\n", practical_manipulation);	
	printf("Ответ: %.1f", result);
   getchar();
   return 0;
}