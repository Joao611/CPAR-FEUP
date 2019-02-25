using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace CPAR
{
    class Matrix
    {
    

    static int[][] GenerateMatrix(int size){
         int[][] matrix = new int[size][];

            for(int i=0; i<size; i++)
            {
                int[] row = new int[size];
                for(int j=0; j<size; j++)
                {
                    row[j] = i+1;
                }
                matrix[i] = row;
            }

    return matrix;

    }

    static int[][] GenerateIdentityMatrix(int size){

        int[][] matrix = new int[size][];

            for(int i=0; i<size; i++)
            {
                int[] row = new int[size];
                for(int j=0; j<size; j++)
                {
                    row[j] = 1;
                }
                matrix[i] = row;
            }

    return matrix;
        
    }

    static int[][] multMatrices(int[][] m1, int[][] m2, int n)
        {
            int[][] m3 = new int[n][];

            for (int i = 0; i < n; i++)
            {
                int[] row = new int[n];
                for (int j = 0; j < n; j++)
                {
                    int cell = 0;
                    for (int t = 0; t < n; t++)
                    {
                        cell += m1[i][t] * m2[t][j];
                    }
                    row[j] = cell;
                }
                m3[i] = row;
            }

            return m3;
    }


     static void Main(string[] args){
          Console.WriteLine("Choose a number for the matrix");
         int n = int.Parse(Console.ReadLine());
           int[][] m1 = GenerateMatrix(n);
            int[][] m2 = GenerateIdentityMatrix(n);
            Stopwatch sw = Stopwatch.StartNew();
             int[][] m3=multMatrices(m1, m2, n);
              double elapsed = sw.ElapsedMilliseconds;
            sw.Stop();
             Console.WriteLine(n+"x"+n);
                Console.WriteLine(String.Format("Time: {0:0.00}",elapsed/1000));
                Console.WriteLine();

            //  for(int i=0; i<n; i++)
            // {
            //     for(int j=0; j<n; j++)
            //     {
            //         Console.Write("|"+m3[i][j]);
            //     }
            //     Console.WriteLine("|");
            // }
    Console.WriteLine();
         
         

     }




    }
}
