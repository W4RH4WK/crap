#include <stdio.h>

enum phone_type {
	PHONE_TYPE_HOME,
	PHONE_TYPE_WORK,
};

int main()
{
	enum phone_type pt = PHONE_TYPE_HOME;

	// Note: Missing case
	switch (pt) {
	case PHONE_TYPE_WORK:
		puts("work");
		break;
	}
}
