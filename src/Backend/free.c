#include "back.h"

/*
	\brief Дарит мир во всём мире (геноцид структур)
*/
void res_free(res *syst) {
  for (int i = 0; i < syst->amountFacets; i++)
    if (syst->face[i].f) free(syst->face[i].f);
  if (syst->face) free(syst->face);
  if (syst->vert.coord) free(syst->vert.coord);
  memset(syst, 0, sizeof(res));
}
