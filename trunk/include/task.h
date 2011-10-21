
#pragma warning(push)
#pragma warning(disable:4510)
#pragma warning(disable:4512)
#pragma warning(disable:4610)

struct Task
{
   const char *name;
   const char *desc;
   bool (*func)(const char*, char**);
};

#ifndef TASK_NAME
#define TASK_NAME(NAME) task_##NAME
#endif

#ifndef STRING
#define STRING(x) #x
#endif

#pragma warning(pop)

#ifndef TASK_STRUCT
#define TASK_STRUCT(NAME, DESC)\
struct Task TASK_NAME(NAME) =\
{\
   STRING(NAME),\
   DESC,\
   fun##NAME\
};
#endif
