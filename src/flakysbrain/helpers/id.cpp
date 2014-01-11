#include "id.h"

static Id next_id = 0;

Id createId()
{
    return next_id++;
}
