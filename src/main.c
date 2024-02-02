#include <Windows.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CVT_TO_LOCAL(time) (time + utc_offset)
#define CVT_TO_HOUR_OF_DAY(time) (CVT_TO_LOCAL(time) % (24 * 60 * 60))

const char *
get_current_day(const time_t ms_since_epoch)
{
	static const char const days[][14] = {
		"thursday.txt",
		"friday.txt",
		"saturday.txt",
		"sunday.txt",
		"monday.txt",
		"tuesday.txt",
		"wednesday.txt"
	};

	char *return_buffer = malloc(14 * sizeof(char));
	memcpy(return_buffer, days[ms_since_epoch / 60 / 60 / 24 % 7], 14);
}

static inline long
get_utc_offset()
{
	static TIME_ZONE_INFORMATION tz_info;
	GetTimeZoneInformation(&tz_info);
	return tz_info.Bias;
}

int
main()
{
	const long   utc_offset		= get_utc_offset() * -1 * 60;
	const time_t current_time = time(NULL);

	const char *const day_str = get_current_day(current_time);
	
	FILE *file_descriptor = fopen(day_str, "rb");
	fseek(file_descriptor, 0, SEEK_END);
	const long file_length = ftell(file_descriptor);
	fseek(file_descriptor, 0, SEEK_SET);

	char *data = malloc(file_length * sizeof(char));

	do
	{
		int from_hours, from_minutes;
		int to_hours, to_minutes;
		char s[5];
		fscanf(file_descriptor, "%d:%d-%d:%d%*[ ]%s", &from_hours, &from_minutes, &to_hours, &to_minutes, s);

		if (feof(file_descriptor))
		{
			puts("No subject scheduled at this hour!");
			break;
		}

		// Convert to_hours to seconds
		from_hours  = (from_hours * 60 * 60) + (from_minutes * 60);
		to_hours 		= (to_hours * 60 * 60) + (to_minutes * 60);

#ifdef DEBUG
		fprintf(stderr, "[DEBUG] Start of %s == %d\n[DEBUG] End of %s == %d\n[DEBUG] Current Hour: %d\n", s, from_hours, s, to_hours, CVT_TO_HOUR_OF_DAY(current_time));
#endif // DEBUG

		if (CVT_TO_HOUR_OF_DAY(current_time) >= from_hours && CVT_TO_HOUR_OF_DAY(current_time) <= to_hours)
		{
			printf("Current Subject is: %s\n", s);
			break;
		}
	} while (1);
	return 0;
}
