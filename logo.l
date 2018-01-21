%{
#include "logo_type.h"
#include "logo.tab.h"

%}

%%
[1-9][0-9]*    {yylval.val = atoi(yytext); return ENTIER;}
FORWARD        {return TK_FORWARD;}
CIRCLE         {return TK_CIRCLE;}
MOVE		      {return TK_MOVE;}
LEFT           {return TK_LEFT;}
RIGHT          {return TK_RIGHT;}
REPEAT         {return TK_REPEAT;}
SAVE           {return TK_SAVE;}
RECALL         {return TK_RECALL;}
\$[A-Z]+       {yylval.strval = strdup(yytext); return NAME;}
\[             {return TK_BEGIN;}
\]             {return TK_END;}
%%
