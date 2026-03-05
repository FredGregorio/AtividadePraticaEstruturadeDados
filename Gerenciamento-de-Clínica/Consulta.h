#ifndef CONSULTA_H
#define CONSULTA_H



void salvarConsultas(Consulta *consultas, int total, const char *modo);

void listarConsultas();

void alterarStatusConsulta(enum statusConsulta novoStatus);

void menuConsultas();

#endif