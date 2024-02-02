# Usage
Simply run the program by executing `.\subject-now.exe`.
You should get "Current Subject: [SUBJECT_CODE]" if there is a subject up at the time, "No subject up for now" if otherwise.

# Schedule Format
The program works by reading a pre-made schedule, written in 7 files (representing each day of the week).
The files represent the schedule for that one day.
The schedule should abide by the following format:

```
STARTING_TIME_IN_HOUR_PART:STARTING_TIME_MINUTE_PART:ENDING_TIME_HOUR_PART:ENDING_TIME_MINUTE_PART SUBJECT_CODE
```

Example:
```
07:00-08:00 MATH
```
