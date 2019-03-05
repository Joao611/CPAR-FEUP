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


        static int[][] GenerateMatrix(int size)
        {
            int[][] matrix = new int[size][];

            for (int i = 0; i < size; i++)
            {
                int[] row = new int[size];
                for (int j = 0; j < size; j++)
                {
                    row[j] = i + 1;
                }
                matrix[i] = row;
            }

            return matrix;

        }

        static int[][] GenerateIdentityMatrix(int size)
        {

            int[][] matrix = new int[size][];

            for (int i = 0; i < size; i++)
            {
                int[] row = new int[size];
                for (int j = 0; j < size; j++)
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
                    for (int k = 0; k < n; k++)
                    {
                        cell += m1[i][k] * m2[k][j];
                    }
                    row[j] = cell;
                }
                m3[i] = row;
            }

            return m3;
        }

        static int[][] multMatricesLine(int[][] m1, int[][] m2, int n)
        {
            int[][] m3 = new int[n][];

            for (int i = 0; i < n; i++)
            {
                int[] row = new int[n];
                for (int k = 0; k < n; k++)
                {

                    for (int j = 0; j < n; j++)
                    {
                        row[j] += m1[i][k] * m2[k][j];
                    }
                }
                m3[i] = row;
            }

            return m3;
        }


        static void Main(string[] args)
        {
            Console.WriteLine("Choose an option:");
            Console.WriteLine("1-normal mult");
            Console.WriteLine("2-line mult");
            int option = int.Parse(Console.ReadLine());
            // Console.WriteLine("Choose a number for the matrix");
            // int n = int.Parse(Console.ReadLine());
            // int[][] m2 = GenerateMatrix(n);
            // int[][] m1 = GenerateIdentityMatrix(n);
            
            // int[][] m3 = { };
            for(int h=600;h<=3000;h+=400){
                int[][] m2 = GenerateMatrix(h);
            int[][] m1 = GenerateIdentityMatrix(h);
            
            int[][] m3 = { };
           // if (option == 1)
           Stopwatch sw = Stopwatch.StartNew();
                m3 = multMatrices(m1, m2, h);
                sw.Stop();
           // else if (option == 2)
           Stopwatch sw2 = Stopwatch.StartNew();
                m3 = multMatricesLine(m1, m2, h);
                sw2.Stop();
            double elapsed = sw.ElapsedMilliseconds;
            double elapsed2 = sw2.ElapsedMilliseconds;
            
            Console.WriteLine( "size:" + h);
            Console.WriteLine(String.Format("Time normal algorithm: {0:0.00}", elapsed / 1000));
            Console.WriteLine(String.Format("Time modified algorithm: {0:0.00}", elapsed2 / 1000));
            Console.WriteLine();
            }
            // for (int i = 0; i < 10; i++)
            // {
            //     for (int j = 0; j < 10; j++)
            //     {
            //         Console.Write("|" + m1[i][j]);
            //     }
            //     Console.WriteLine("|");

            // }
            // Console.WriteLine();

            // for (int i = 0; i < 10; i++)
            // {
            //     for (int j = 0; j < 10; j++)
            //     {
            //         Console.Write("|" + m2[i][j]);
            //     }
            //     Console.WriteLine("|");
            // }
            // Console.WriteLine();

            // for (int i = 0; i < 10; i++)
            // {
            //     for (int j = 0; j < 10; j++)
            //     {
            //         Console.Write("|" + m3[i][j]);
            //     }
            //     Console.WriteLine("|");
            // }
            // Console.WriteLine();



        }




    }
}
