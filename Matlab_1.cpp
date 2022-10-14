 #include <iostream>
 #include <fstream>
 #include <string>

double* gauss(double **A, double *B, int n) { 
  double *X, max; int k = 0, index;
  X = new double[n];
  while (k < n)
  { 
    max = abs(A[k][k]);
    index = k;
    for (int i = k; i < n; i++) {
      if (abs(A[i][k]) > max) {
        max = abs(A[i][k]);
        index = i;
      }
    }

    for (int j = 0; j < n; j++) {
      double temp = A[k][j];
      A[k][j] = A[index][j];
      A[index][j] = temp;
    }
    double temp = B[k];
    B[k] = B[index];
    B[index] = temp;

    for (int i = k; i < n; i++) 
    {
      double temp = A[i][k];
      if (temp == 0) continue;
      for (int j = 0; j < n; j++) { A[i][j] /= temp;}
      B[i] /= temp;

      if (i == k) continue;
      for (int j = 0; j < n; j++) { A[i][j] -= A[k][j];}
      B[i] -= B[k];
    }
    k++;
  }


  for (k = n - 1; k >= 0; k--)
  {
    X[k] = B[k];
    for (int i = k; i >= 0; i--)
      B[i] = B[i] - A[i][k] * X[k];
  }
  return X;
}


// int main() { double **A, *B, *X; int n;
//   A = new double *[n];
//   for (int i = 1; i <= n; i++) {A[i] = new double [n];}
//   std::cout << "Введите значения матрицы А: " << std::endl;
//     for (int i = 1; i <= n; i++) {   
//         for (int j = 1; j <= n; j++) { std::cin >> A[i][j];} 
//     }
//     std::cout << "Введите Значения матрицы В: " << std::endl;
//     B = new double[n];
//     for (int i = 1; i <= n; i++) { std::cin >> B[i];}


int main() {
  int n, c = 0;
  std::string line;
  std::string delimiter = " ";
  size_t pos = 0;

  std::ifstream input_file(R"(C:\Users\yana\Desktop\Matrix.txt)", std::ios::in);
  getline(input_file, line);
  n = std::stoi(line);

  double **A = new double *[n];
  double *B = new double[n];

  for (int i = 0; i < n; i++) {
      A[i] = new double [n];
      c = 0;
      getline(input_file, line);
      std::string token;
      while ((pos = line.find(delimiter)) != std::string::npos) {
          token = line.substr(0, pos);
          line.erase(0, pos + delimiter.length());
          auto t = std::stod(token);
          A[i][c] = t;
          c++;
      }
      B[i] = std::stod(line);
  }
  input_file.close();

  auto X = gauss(A, B, n);
  for (int i = 0; i < n; i++) {std::cout << "x[" << i << "]=" << X[i] << " ";}


  std::ofstream output_file;
  output_file.open(R"(C:\Users\yana\Desktop\Answer.txt)", std::ios::out);
  for (int i = 0; i < n; i++) {
      output_file << "x[" << i << "]=" << X[i] << " ";
  }
  output_file.close();
  return 0;
}