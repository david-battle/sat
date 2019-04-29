#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLAUSES 1000
#define MAX_VARS 30
#define MAX_LINE 100

char buf[MAX_LINE];
char cnf[4];

int nvars;
int nclauses;
int b[MAX_CLAUSES][MAX_VARS];

void read_input()
{
  int literal;
  int clause;
  int tmp;

  do {
    if(fgets(buf, sizeof(buf), stdin) == NULL)
      break;
  } while(buf[0] != 'p');
  if(sscanf(buf, "%*s %3s %d %d\n", cnf, &nvars, &nclauses) != 3 ||
     strcmp(cnf, "cnf") != 0 ||
     nvars > MAX_VARS ||
     nclauses > MAX_CLAUSES) {
    printf("Error.\n");
    exit(1);
  }
  for(clause = 0; clause < nclauses; clause++) {
    for(literal =0; scanf("%d", &tmp) == 1 && tmp != 0; literal++) {
      b[clause][literal] = tmp;
    }
  }
}

#define bit(var,pos) ((var) & (1L<<((pos)-1)))

void solve()
{
  unsigned long s;
  int c, l, v;

  for(s = 0; s < 1L<< nvars; s++) {
    for(c= 0; c < nclauses; c++) {
      for(l = 0; b[c][l] && ((b[c][l]<0) ? (bit(s,-b[c][l])): (!bit(s, b[c][l]))); l++);
      if(b[c][l] == 0) {
	break;
      }
    }
    if(c == nclauses) {
      break;
    }
  }
  if(s == (1L<<nvars)) {
    printf("UNSATISFIABLE\n");
  }
  else {
    /*    printf("SATISFIABLE %08x\n", s); */
    printf("SATISFIABLE\n");
    for(v = 1; v <= nvars; v++) {
      printf("%s%d ", bit(s,v)?"":"-", v);
    }
    printf(" 0\n");
  }
}

int
main()
{
  read_input();
  solve();
}
