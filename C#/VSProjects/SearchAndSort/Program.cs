using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assessment1
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Roads> ObjectList = new List<Roads>();

            string[] Road1Lines = System.IO.File.ReadAllLines("Road_1_256.txt");
            string[] Road2Lines = System.IO.File.ReadAllLines("Road_2_256.txt");
            string[] Road3Lines = System.IO.File.ReadAllLines("Road_3_256.txt");
            string[] bigRoad1Lines = System.IO.File.ReadAllLines("Road_1_2048.txt");
            string[] bigRoad2Lines = System.IO.File.ReadAllLines("Road_2_2048.txt");
            string[] bigRoad3Lines = System.IO.File.ReadAllLines("Road_3_2048.txt");

            Roads Road1 = new Roads(Road1Lines);
            Roads Road2 = new Roads(Road2Lines);
            Roads Road3 = new Roads(Road3Lines);
            Roads bigRoad1 = new Roads(bigRoad1Lines);
            Roads bigRoad2 = new Roads(bigRoad2Lines);
            Roads bigRoad3 = new Roads(bigRoad3Lines);

            ObjectList.Add(Road1);
            ObjectList.Add(Road2);
            ObjectList.Add(Road3);
            ObjectList.Add(bigRoad1);
            ObjectList.Add(bigRoad2);
            ObjectList.Add(bigRoad3);

            string selectRoad = "";
            string algorithm = "";
            string selectSearch;
            string selectValue;
            
            List<int> foundValues;

            bool correctAlgInput = false;
            bool correctFileInput = false;
            bool correctSearchInput = false;

            while (correctAlgInput == false || correctFileInput == false)
            {
                Console.WriteLine("Please select a file to sort: List1(1), List2(2), List3(3), List1 2048(4), List2 2048(5), List3 2048(6): ");
                selectRoad = Console.ReadLine();
                if (selectRoad != "1" && selectRoad != "2" && selectRoad != "3" && selectRoad != "4" && selectRoad != "5" && selectRoad != "6")
                {
                    correctFileInput = false;
                    Console.WriteLine("Please input a a correct option");
                }
                else
                {
                    correctFileInput = true;
                    Console.WriteLine("Please choose a sort algorithm: bubble(1), insertion(2) or merge(3) ");
                    algorithm = Console.ReadLine();
                }


                if (algorithm == "1")
                {
                    correctAlgInput = true;

                    string[] bubbleSortList = ObjectList[Int32.Parse(selectRoad) - 1].BubbleSort();
                    for (int i = 0; i < bubbleSortList.Length; i += 10)
                    {
                        Console.WriteLine("\t" + bubbleSortList[i]);
                    }

                    string[] bubleSortListR = ObjectList[Int32.Parse(selectRoad) - 1].ReverseBubbleSort();
                    for (int i = 0; i < bubleSortListR.Length; i += 10)
                    {
                        Console.WriteLine("\t" + bubleSortListR[i]);
                    }
  
                }

                else if (algorithm == "2")
                {
                    correctAlgInput = true;

                    string[] insertionList = ObjectList[Int32.Parse(selectRoad) - 1].InsertionSort();
                    for (int i = 0; i < insertionList.Length; i += 10)
                    {
                        Console.WriteLine("\t" + insertionList[i]);
                    }

                    string[] insertionListR = ObjectList[Int32.Parse(selectRoad) - 1].ReverseInsertionSort();
                    for (int i = 0; i < insertionListR.Length; i += 10)
                    {
                        Console.WriteLine("\t" + insertionListR[i]);
                    }
       
                }

                else if (algorithm == "3")
                {
                    Console.WriteLine("=====This is every 10th value of the sorted road using insertion sort=====");
                    correctAlgInput = true;
                    string[] mergeFile = ObjectList[Int32.Parse(selectRoad) - 1].sortedFile;
                    int l = 0;
                    int r = mergeFile.Length - 1;
                    string[] sortedMergeFile = ObjectList[Int32.Parse(selectRoad) - 1].MergeSort(mergeFile, l, r);
                    for (int i = 0; i < sortedMergeFile.Length; i += 10)
                    {
                        Console.WriteLine("\t" + sortedMergeFile[i]);
                    }

                    Console.WriteLine("=====This is every 10th value of the reverse sorted road using insertion sort=====");
                    for (int i = sortedMergeFile.Length - 1; i > 0; i -= 10)
                    {
                        Console.WriteLine("\t" + sortedMergeFile[i]);
                    }

                }

                else if (correctFileInput == true)
                {
                    Console.WriteLine("Please input a a correct option");
                    correctAlgInput = false;
                }

            }
                
            while (correctSearchInput == false)
            {
                Console.WriteLine("Please select a search algorithm: linear search(1), binary search(2): ");
                selectSearch = Console.ReadLine();
                Console.WriteLine("Please select value you want to search for: ");
                selectValue = Console.ReadLine();
                if (int.TryParse(selectValue, out int value))
                {
                    if (selectSearch == "1")
                    {
                        correctSearchInput = true;
                        foundValues = ObjectList[Int32.Parse(selectRoad) - 1].LinearSearch(value.ToString());                     
                        for (int i = 0; i < foundValues.Count; i++) //finding all pos of value
                        {
                            Console.WriteLine("\t" + foundValues[i]);
                        }
                    }

                    else if (selectSearch == "2")
                    {
                        correctSearchInput = true;
                        foundValues = ObjectList[Int32.Parse(selectRoad) - 1].BinarySearch(value.ToString());
                        
                        for (int i = 0; i < foundValues.Count; i++) //finding all pos of value
                        {
                            Console.WriteLine("\t" + foundValues[i]);
                        }
                    }

                    else
                    {
                        correctSearchInput = false;
                        Console.WriteLine("Please input a correct option");
                    }
                }

                else
                {
                    correctSearchInput = false;
                    Console.WriteLine("Please input a correct option");
                } 
            }
            selectSearch = Console.ReadLine();
        }
    }

    public class Roads
    {
        public string[] file;
        public string[] sortedFile;
        public string[] reverseSortedFile;
        public int counter;
        public Roads(string[] roadFile)
        {
            file = roadFile;
            sortedFile = file.Clone() as string[];
            reverseSortedFile = file.Clone() as string[];
            counter = 0;
        }
        public string[] BubbleSort()
        {
            counter = 0;
            sortedFile = file.Clone() as string[];
            string tempValue;
            Console.WriteLine("=====This is every 10th value of the sorted road using bubble sort=====");
            for (int pass = 0; pass < sortedFile.Length; pass++)
            {
                for (int value = 0; value < sortedFile.Length - 1; value++)
                {
                    counter++;
                    if (Int32.Parse(sortedFile[value]) > Int32.Parse(sortedFile[value + 1]))
                    {
                        tempValue = sortedFile[value + 1];
                        sortedFile[value + 1] = sortedFile[value];
                        sortedFile[value] = tempValue;
                        
                    }
                }
            }
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return sortedFile;
        }

        public string[] ReverseBubbleSort()
        {
            counter = 0;
            reverseSortedFile = file.Clone() as string[];
            string tempValue;
            Console.WriteLine("=====This is every 10th value of the reverse sorted road using bubble sort=====");
            for (int pass = 0; pass < reverseSortedFile.Length; pass++)
            {
                for (int value = 0; value < reverseSortedFile.Length - 1; value++)
                {
                    counter++;
                    if (Int32.Parse(reverseSortedFile[value]) < Int32.Parse(reverseSortedFile[value + 1]))
                    {
                        tempValue = reverseSortedFile[value + 1];
                        reverseSortedFile[value + 1] = reverseSortedFile[value];
                        reverseSortedFile[value] = tempValue;
                    }
                }
            }
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return reverseSortedFile;
        }

        public string[] InsertionSort()
        {
            counter = 0;
            int movingIndex;
            int item;
            sortedFile = file.Clone() as string[];
            Console.WriteLine("=====This is every 10th value of the sorted road using insertion sort=====");
            for (int i = 0; i < sortedFile.Length; i++)
            {
                item = Int32.Parse(sortedFile[i]);
                movingIndex = i;

                while (movingIndex > 0 && Int32.Parse(sortedFile[movingIndex - 1]) > item)
                {
                    sortedFile[movingIndex] = sortedFile[movingIndex - 1];
                    movingIndex--;
                    counter++;
                }

                sortedFile[movingIndex] = item.ToString();
            }
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return sortedFile;
        }

        public string[] ReverseInsertionSort()
        {
            counter = 0;
            int movingIndex;
            int item;
            reverseSortedFile = file.Clone() as string[];
            Console.WriteLine("=====This is every 10th value of the reverse sorted road using insertion sort=====");
            for (int i = 0; i < reverseSortedFile.Length; i++)
            {
                item = Int32.Parse(reverseSortedFile[i]);
                movingIndex = i;

                while (movingIndex > 0 && Int32.Parse(reverseSortedFile[movingIndex - 1]) < item)
                {
                    reverseSortedFile[movingIndex] = reverseSortedFile[movingIndex - 1];
                    movingIndex--;
                    counter++;
                }

                reverseSortedFile[movingIndex] = item.ToString();
            }
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return reverseSortedFile;
        }

        public void Merge(string[] sortFile, int left, int middle, int right)
        {
            int branch1Size = middle - left + 1;
            int branch2Size = right - middle;

            int[] leftBranch = new int[branch1Size];
            int[] rightBranch = new int[branch2Size];
            int i, j;

            for (i = 0; i < branch1Size; i++)
                leftBranch[i] = Int32.Parse(sortFile[left + i]);
            for (j = 0; j < branch2Size; j++)
                rightBranch[j] = Int32.Parse(sortFile[middle + 1 + j]);

            i = 0;
            j = 0;

            int k = left;
            while (i < branch1Size && j < branch2Size)
            {
                counter++;
                if (leftBranch[i] <= rightBranch[j])
                {
                    sortFile[k] = leftBranch[i].ToString();
                    i++;
                }
                else
                {
                    sortFile[k] = rightBranch[j].ToString();
                    j++;
                }
                k++;
            }

            while (i < branch1Size)
            {
                counter++;
                sortFile[k] = leftBranch[i].ToString();
                i++;
                k++;
            }

            while (j < branch2Size)
            {
                counter++;
                sortFile[k] = rightBranch[j].ToString();
                j++;
                k++;
            }
        }

        public string[] MergeSort(string[] sortFile, int left, int right)
        {
            counter++;
            if (left < right)
            {
                int middle = left + (right - left) / 2;
            
                MergeSort(sortFile, left, middle);
                MergeSort(sortFile, middle + 1, right);
               
                Merge(sortFile, left, middle, right);
                
            }
            
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return sortFile;

        }
        public List<int> LinearSearch(string value)
        {
            counter = 0;
            List<int> positions = new List<int>();
            for(int i = 0; i < sortedFile.Length; i++)
            {
                counter++;
                if(sortedFile[i] == value)
                {
                    positions.Add(i);
                }
            }
            Console.WriteLine("=====This is a linear search for the value: " + value + ". Its positions are:=====");
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return positions;
        }

        public List<int> BinarySearch(string value)
        {
            counter = 0;
            bool sorted = false;
            List<int> positions = new List<int>();
            int min = 0;
            int max = sortedFile.Length - 1;
            List<string> searchFile = new List<string>(sortedFile);
            while (min <= max && sorted == false)
            {
                counter++;
                int middle = (min + max) / 2;
                if (value == searchFile[middle])
                {
                    positions.Add(middle);
                    positions = BinaryBounds(value, middle, positions);
                    sorted = true;
                }
                
                else if (Int32.Parse(value) < Int32.Parse(searchFile[middle]))
                {
                    max = middle - 1;             
                }
                else
                {
                    min = middle + 1;
                }
            }
            Console.WriteLine("=====This is a binary search for the value: " + value + ". Its positions are:=====");
            Console.WriteLine("The number of steps for this algorithm is: " + counter);
            return positions;
        }

        public List<int> BinaryBounds(string value, int index, List<int> positions)
        {
            int upper = index + 1;
            int lower = index - 1;
            bool rangeCompU = false;
            bool rangeCompL = false;
            bool outOfRangeU = false;
            bool outOfRangeL = false;
            while (rangeCompL == false && rangeCompU == false)
            {
                if (lower < 0)
                {
                    outOfRangeL = true;
                }
                if (upper == sortedFile.Length)
                {
                    outOfRangeU = true;
                }
                if (outOfRangeL == false)
                {
                    if (sortedFile[lower] == value)
                    {
                        positions.Add(lower);
                        lower--;
                    }
                    else
                    {
                        rangeCompL = true;
                    }
                }
                if (outOfRangeU == false)
                {
                    if (sortedFile[upper] == value)
                    {
                        positions.Add(upper);
                        upper++;
                    }
                    else
                    {
                        rangeCompU = true;
                    }
                }
                

            }

            return positions;
            
        }
    }
}

