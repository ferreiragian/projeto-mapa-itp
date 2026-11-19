#include "paleta.h"
#include <fstream>
#include <string>

// converte um caractere hexadecimal (0-9, a-f, A-F) em seu valor inteiro
static int valorHex(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  }
  if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }
  return 0;
}

Paleta::Paleta(int tamanho) {
  this->tamanho = tamanho;
  this->quantidade = 0;
  this->cores = new Cor[tamanho];
}

Paleta::Paleta(const std::string& nomeArquivo) {
  this->tamanho = contarCoresArquivo(nomeArquivo);
  this->quantidade = 0;
  this->cores = new Cor[this->tamanho];

  std::ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    return;
  }

  std::string linha;
  while (quantidade < tamanho && std::getline(arquivo, linha)) {
    if (linha.size() < 7 || linha[0] != '#') {
      continue;
    }

    Cor cor;
    cor.r = valorHex(linha[1]) * 16 + valorHex(linha[2]);
    cor.g = valorHex(linha[3]) * 16 + valorHex(linha[4]);
    cor.b = valorHex(linha[5]) * 16 + valorHex(linha[6]);

    adicionarCor(cor);
  }

  arquivo.close();
}

Paleta::~Paleta() {
  delete[] cores;
}

int Paleta::obterTamanho() const {
  return tamanho;
}

int Paleta::obterQuantidade() const {
  return quantidade;
}

void Paleta::adicionarCor(const Cor& cor) {
  if (quantidade < tamanho) {
    cores[quantidade] = cor;
    quantidade++;
  }
}

Cor Paleta::obterCor(int indice) {
  if (indice < 0 || indice >= quantidade) {
    return Cor {0, 0, 0};
  }
  return cores[indice];
}

int Paleta::contarCoresArquivo(const std::string& nomeArquivo) const {
  std::ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    return 0;
  }

  int total = 0;
  std::string linha;
  while (std::getline(arquivo, linha)) {
    if (linha.size() >= 7 && linha[0] == '#') {
      total++;
    }
  }

  arquivo.close();
  return total;
}