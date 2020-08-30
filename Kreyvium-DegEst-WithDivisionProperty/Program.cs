using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Gurobi;
namespace gorubi
{
    class Program
    {
        static void Main(string[] args)
        {
            //for (int i = 0; i < 26; i++)
            //    Console.Write(3*i + ",");
            //Console.ReadKey();
            GRBEnv env=new GRBEnv("Kreyium.log");
            
            int round=892;
            
            GRBModel model = new GRBModel(env);
            int[] pos = new int[7] { 65, 92, 161, 176, 242, 287,415};//7个输出位置
            GRBVar[] s = model.AddVars(544, GRB.BINARY);
            for (int i = 0; i < 544; i++)
                s[i].VarName = "var" + i.ToString();//288个寄存器,命名为var0-var288
            char[] FlagS = new char[544];//288个寄存器的Flag
            GRBVar[] NewVars = model.AddVars(34 * round, GRB.BINARY);
            for (int i = 0; i < NewVars.Length; i++)
                NewVars[i].VarName = "y" + i.ToString();//每过一次更新许需要加30个变量，总共为30*round,命名为y0-y300*round

            char[] FlagNewVars = new char[34 * round];//新加变量的Flag
            GRBVar[] IV = model.AddVars(128, GRB.BINARY);
            for (int i = 0; i < 128; i++)
                IV[i].VarName = "IV" + i.ToString();//128个IV变量

            GRBVar[] Key = model.AddVars(128, GRB.BINARY);
            for (int i = 0; i < 128; i++)
                Key[i].VarName = "Key" + i.ToString();//128个Key变量


            // List<uint> cube = new List<uint>() { 1, 3, 5, 7, 9, 11, 13, 16, 18, 20, 22, 24, 26, 28, 31, 33, 35, 37, 39, 41, 43, 46,
            //                                      48, 50, 52, 54, 61, 63, 65, 67, 69, 71, 73, 76, 78, 80, 82, 84, 86, 88, 90, 92, 95,
            //                                      97, 99, 101, 103, 106, 108, 110, 112, 114, 116, 118, 120, 125, 127};//cube变量
            //dcc19
            // List<uint> cube = new List<uint>() { 0,2,4,6,8,10,12,15,17,19,21,24,26,28,30,32,34,36,39,41,43,45,47,49,52,54,56,58,
            //                                      60,62,67,69,71,73,75,80,82,84,86,89,91,93,95,97,99,102,104,106,108,110,112,114,
            //                                      117,119,121,123};//cube变量
            //List<uint> cube = new List<uint>() {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 37, 39, 41, 43, 45, 46, 47, 48, 49, 50, 51, 52, 54, 56, 59, 61, 63, 65, 67, 69, 71, 74, 76, 78, 80, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
            //dis880 try 892
            //List<uint> cube =new List<uint>(){0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,29,31,33,35,37,39,41,44,46,48,50,52,54,56,59,61,63,65,67,69,72,74,76,78,80,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127};
           List<uint> cube =new List<uint>(){0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,35,37,39,41,43,44,45,46,47,48,49,50,52,54,57,59,61,63,65,67,69,72,74,76,78,80,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127};
            List<int> keyset= new List<int>(){};
            for(int i=0;i<128;i++)
            {
                keyset.Add(i);
            }
            for(int i=0;i<cube.Count();i++)
            {
                Console.Write(cube[i]+" ");
            }
            Console.WriteLine();
            List<UInt32> Noncube = new List<uint>() { 0x0,0x0,0x0,0x0};
            GRBLinExpr ChooseKey = new GRBLinExpr();//超多项式中可能含有的密钥变量集合
            int VarNumber = 0;
            initial(model, s, FlagS, cube, Noncube, keyset, ChooseKey, IV, Key);//初始化设置
            for (int i = 1; i <=round; i++)
                Triviumcore(model, s,FlagS, NewVars, FlagNewVars,ref VarNumber);

            for (int i = 0; i < 544; i++)
            {
                if (!pos.Contains(i))
                {
                    model.AddConstr(s[i] == 0, "a" + i.ToString());
                }
            }
            GRBLinExpr expr = new GRBLinExpr();
            for (int i = 0; i < 7; i++)
                expr.AddTerm(1.0, s[pos[i]]);
            model.AddConstr(expr == 1, "t1");
            model.Optimize();
            
            if (model.SolCount > 0)
                Console.WriteLine(model.ObjVal);
            else
                {
                    Console.WriteLine("************************************");
                    Console.WriteLine("Model is infeasible!!!");
                    Console.WriteLine("************************************");
                }
            model.Dispose();
            env.Dispose();
            Console.ReadKey();
        }
        static void initial(GRBModel model, GRBVar[] s, char[] FlagS, List<uint> cube, List<UInt32> Noncube, List<int> keyset, GRBLinExpr ChooseKey, GRBVar[] IV, GRBVar[] Key)
        {
            //密钥变元
            for (int i = 0; i < 128; i++)
            {
                if (i < 93)
                {
                    if (keyset.Contains(i))
                    {
                        model.AddConstr(Key[i] == 0, "Key" + i.ToString());
                        model.AddConstr(s[i] + s[i + 288] == Key[i], "z" + i.ToString());
                        FlagS[i] = '2';
                        FlagS[i + 288] = '2';
                    }
                    else
                    {
                        model.AddConstr(Key[i] == 0, "Key" + i.ToString());
                        model.AddConstr(s[i] + s[i + 288] == Key[i], "z" + i.ToString());
                        FlagS[i] = '0';
                        FlagS[i + 288] = '0';
                    }
                }
                else
                {
                    model.AddConstr(Key[i] == 0, "Key" + i.ToString());
                    model.AddConstr(s[i + 288] == Key[i], "z" + i.ToString());
                    FlagS[i + 288] = '0';
                }
            }
            //IV 变元
            if (Noncube.Count == 0)
            {
                for (uint i = 0; i < 128; i++)
                {
                    if (cube.Contains(i))
                    {
                        model.AddConstr(IV[i] == 1, "IV" + i.ToString());
                        model.AddConstr(s[i + 93] + s[i + 416] == IV[i], "z" + (i + 128).ToString());
                    }
                    else
                    {
                        model.AddConstr(IV[i] == 0, "z" + i.ToString());
                        model.AddConstr(s[i + 93] + s[i + 416] == IV[i], "z" + (i + 128).ToString());
                    }
                    FlagS[i + 93] = '2';
                    FlagS[i + 416] = '2';
                } 
            }
            else
            {
                for (uint i = 0; i < 128; i++)
                {
                    
                    if (cube.Contains(i))
                    {
                        
                        model.AddConstr(IV[i] == 1, "IV" + i.ToString());
                        model.AddConstr(s[i + 93] + s[i + 416] == IV[i], "z" + (i + 128).ToString());
                        FlagS[i + 93] = '2';
                        FlagS[i + 416] = '2';
                        
                    }
                    else
                    {
                        model.AddConstr(IV[i] == 0, "IV" + i.ToString());
                        model.AddConstr(s[i + 93] + s[i + 416] == IV[i], "z" + (i + 128).ToString());
                        
                        int pos1 = (int)((i) >> 5);
                        int pos2 = (int)(((i) & 0x1f));
                        if (((Noncube[pos1] >> pos2) & 0x01) == 1)
                        {
                            FlagS[i + 93] = '1';
                            FlagS[i + 416] = '1';
                        }
                        else
                        {
                            FlagS[i + 93] = '0';
                            FlagS[i + 416] = '0';
                        }
                    }
                }
            }
            for (int i = 221; i < 287; i++)
            {
                model.AddConstr(s[i] == 0, "s" + i.ToString());
                FlagS[i] = '1';
            }
            model.AddConstr(s[287] == 0, "s" + 287.ToString());
            FlagS[287] = '0';
        }
        static void Triviumcore(GRBModel model, GRBVar[] s, Char[] FlagS, GRBVar[] NewVar, char[] FlagNewVar, ref int VarNumber)
        {
            int[] posA=new int[5]{65,170,90,91,92};
            for (int i = 0; i < 4; i++)
            {
                model.AddConstr(NewVar[VarNumber + 2 * i] + NewVar[VarNumber + 2 * i + 1] == s[posA[i]], "c" + (VarNumber + i).ToString());
                FlagNewVar[VarNumber + 2 * i] = FlagS[posA[i]];
                FlagNewVar[VarNumber + 2 * i+1] = FlagS[posA[i]];
            }
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 5], "c"+(VarNumber + 5).ToString());
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 7], "c"+(VarNumber + 6).ToString());
            FlagNewVar[VarNumber + 8] = FlagMul(FlagNewVar[VarNumber + 5], FlagNewVar[VarNumber + 7]);
            if (FlagNewVar[VarNumber + 8] == '0')
                model.AddConstr(NewVar[VarNumber + 8] == 0, "t" + (VarNumber/10).ToString());
            model.AddConstr(NewVar[VarNumber + 10] + NewVar[VarNumber + 11] == s[543], "c" + (VarNumber + 8).ToString());
            FlagNewVar[VarNumber + 10] = FlagS[543];
            FlagNewVar[VarNumber + 11] = FlagS[543];
            model.AddConstr(NewVar[VarNumber + 9] == s[posA[4]] + NewVar[VarNumber + 8] + NewVar[VarNumber + 1] + NewVar[VarNumber + 3] + NewVar[VarNumber + 10], "c" + (VarNumber + 7).ToString());
            FlagNewVar[VarNumber + 9] = FlagAdd(FlagAdd(FlagAdd(FlagS[posA[4]], FlagNewVar[VarNumber + 8]), FlagAdd(FlagNewVar[VarNumber + 1], FlagNewVar[VarNumber + 3])), FlagNewVar[VarNumber + 10]);
            VarNumber = VarNumber + 12;

            int[]posB= new int[5] { 161, 263, 174,175, 176 };
            for (int i = 0; i < 4; i++)
            {
                model.AddConstr(NewVar[VarNumber + 2 * i] + NewVar[VarNumber + 2 * i + 1] == s[posB[i]], "c" + (VarNumber + i).ToString());
                FlagNewVar[VarNumber + 2 * i] = FlagS[posB[i]];
                FlagNewVar[VarNumber + 2 * i + 1] = FlagS[posB[i]];
            }
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 5], "c" + (VarNumber + 5).ToString());
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 7], "c" + (VarNumber + 6).ToString());
            FlagNewVar[VarNumber + 8] = FlagMul(FlagNewVar[VarNumber + 5], FlagNewVar[VarNumber + 7]);
            if (FlagNewVar[VarNumber + 8] == '0')
                model.AddConstr(NewVar[VarNumber + 8] == 0, "t" + (VarNumber / 10).ToString());
            model.AddConstr(NewVar[VarNumber + 9] == s[posB[4]] + NewVar[VarNumber + 8] + NewVar[VarNumber + 1] + NewVar[VarNumber + 3], "c" + (VarNumber + 7).ToString());
            FlagNewVar[VarNumber + 9] = FlagAdd(FlagAdd(FlagS[posB[4]], FlagNewVar[VarNumber + 8]), FlagAdd(FlagNewVar[VarNumber + 1], FlagNewVar[VarNumber + 3]));
            VarNumber = VarNumber + 10;

            int[] posC = new int[5] { 242, 68, 285, 286, 287 };
            for (int i = 0; i < 4; i++)
            {
                model.AddConstr(NewVar[VarNumber + 2 * i] + NewVar[VarNumber + 2 * i + 1] == s[posC[i]], "c" + (VarNumber + i).ToString());
                FlagNewVar[VarNumber + 2 * i] = FlagS[posC[i]];
                FlagNewVar[VarNumber + 2 * i + 1] = FlagS[posC[i]];
            }
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 5], "c" + (VarNumber + 5).ToString());
            model.AddConstr(NewVar[VarNumber + 8] >= NewVar[VarNumber + 7], "c" + (VarNumber + 6).ToString());
            FlagNewVar[VarNumber + 8] = FlagMul(FlagNewVar[VarNumber + 5], FlagNewVar[VarNumber + 7]);
            if (FlagNewVar[VarNumber + 8] == '0')
                model.AddConstr(NewVar[VarNumber + 8] == 0, "t" + (VarNumber / 10).ToString());
           
            model.AddConstr(NewVar[VarNumber + 10] + NewVar[VarNumber + 11] == s[415], "c" + (VarNumber + 8).ToString());
            FlagNewVar[VarNumber + 10] = FlagS[415];
            FlagNewVar[VarNumber + 11] = FlagS[415];
            model.AddConstr(NewVar[VarNumber + 9] == s[posC[4]] + NewVar[VarNumber + 8] + NewVar[VarNumber + 1] + NewVar[VarNumber + 3] + NewVar[VarNumber + 10], "c" + (VarNumber + 7).ToString());
            FlagNewVar[VarNumber + 9] = FlagAdd(FlagAdd(FlagAdd(FlagS[posC[4]], FlagNewVar[VarNumber + 8]), FlagAdd(FlagNewVar[VarNumber + 1], FlagNewVar[VarNumber + 3])), FlagNewVar[VarNumber + 10]);
            VarNumber = VarNumber + 12;

            for (int i = 287; i > 0; i--)
            {
                s[i] = s[i - 1];
                FlagS[i] = FlagS[i - 1];
            }
            for (int i = 415; i > 288; i--)
            {
                s[i] = s[i - 1];
                FlagS[i] = FlagS[i - 1];
            }
            for (int i = 543; i > 416; i--)
            {
                s[i] = s[i - 1];
                FlagS[i] = FlagS[i - 1];
            }
            s[0] = NewVar[VarNumber - 12 + 9]; FlagS[0] = FlagNewVar[VarNumber - 12 + 9];
            s[287] = NewVar[VarNumber - 12 + 6]; FlagS[287] = FlagNewVar[VarNumber - 12 + 6];
            s[286] = NewVar[VarNumber - 12 + 4]; FlagS[286] = FlagNewVar[VarNumber - 12 + 4];
            s[69] = NewVar[VarNumber - 12 + 2]; FlagS[69] = FlagNewVar[VarNumber - 12 + 2];
            s[243] = NewVar[VarNumber - 12 + 0]; FlagS[243] = FlagNewVar[VarNumber - 12 + 0];

            s[177] = NewVar[VarNumber - 22 + 9]; FlagS[177] = FlagNewVar[VarNumber - 22 + 9];
            s[176] = NewVar[VarNumber - 22 + 6]; FlagS[176] = FlagNewVar[VarNumber - 22 + 6];
            s[175] = NewVar[VarNumber - 22 + 4]; FlagS[175] = FlagNewVar[VarNumber - 22 + 4];
            s[264] = NewVar[VarNumber - 22 + 2]; FlagS[264] = FlagNewVar[VarNumber - 22 + 2];
            s[162] = NewVar[VarNumber - 22 + 0]; FlagS[162] = FlagNewVar[VarNumber - 22 + 0];

            s[93] = NewVar[VarNumber - 34 + 9]; FlagS[93] = FlagNewVar[VarNumber - 34 + 9];
            s[92] = NewVar[VarNumber - 34 + 6]; FlagS[92] = FlagNewVar[VarNumber - 34 + 6];
            s[91] = NewVar[VarNumber - 34 + 4]; FlagS[91] = FlagNewVar[VarNumber - 34 + 4];
            s[171] = NewVar[VarNumber - 34 + 2]; FlagS[171] = FlagNewVar[VarNumber - 34 + 2];
            s[66] = NewVar[VarNumber - 34 + 0]; FlagS[66] = FlagNewVar[VarNumber - 34 + 0];

            s[288] = NewVar[VarNumber - 12 + 11]; FlagS[288] = FlagNewVar[VarNumber - 12 + 11];
            s[416] = NewVar[VarNumber - 34 + 11]; FlagS[416] = FlagNewVar[VarNumber - 34 + 11];
        }
        static char FlagAdd(char FlagA, char FlagB)
        {
            if (FlagA == '0')
            {
                return FlagB;
            }
            else if (FlagA == '1')
            {
                if (FlagB == '0')
                    return FlagA;
                else if (FlagB == '1')
                    return '0';
                else
                    return '2';
            }
            else
            {
                return '2';
            }
            
        }
        static char FlagMul(char FlagA, char FlagB)
        {
            if (FlagA == '0')
            {
                return '0';
            }
            else if (FlagA == '1')
            {
                return FlagB;
            }
            else
            {
                if (FlagB == '0')
                    return '0';
                else
                    return FlagA;
            }
        }
    }
}
