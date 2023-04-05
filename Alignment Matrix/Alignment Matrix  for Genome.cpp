#include <bits/stdc++.h>

using namespace std;

int main()
{
    string parent = "ACACACTA";
    string offspring = "AGCACACA";
    
    cout<<"Parent: "<<parent <<"\n";
    cout<<"Offspring: "<<offspring<<"\n";
    
    int alignment_matrix[offspring.length()+1][parent.length()+1]; 
    
    // Having 2 matrices to store the index of elements for backtracking
    int row[offspring.length()+1][parent.length()+1];
    int column[offspring.length()+1][parent.length()+1];
    
    for(int i = 0; i < offspring.length()+1; i++)
    {
        alignment_matrix[i][0] = 0; // Filling the 1st entry of all rows with 0's
    }

    for(int j = 0; j < parent.length()+1; j++)
    {
        alignment_matrix[0][j] = 0; // Filling the 1st entry of all columns with 0's
    }

    for(int i = 1; i < offspring.length()+1; i++)
    {
        for(int j = 1; j < parent.length()+1; j++)
        {
            alignment_matrix[i][j] = -1; //Filling rest of the entries with a default value of -1
        }
    }
    
    // Scoring algorithm for the aligment matrix
    for(int i = 1; i < offspring.length() + 1; i++)  
    {
        for(int j = 1; j < parent.length() + 1; j++)
        {
            //In case of a match
            if(offspring[i-1] == parent[j-1])
            {
                alignment_matrix[i][j] = 2 + alignment_matrix[i-1][j-1];
                row[i][j] = i-1;
                column[i][j] = j-1;
            }
            
            //In case of a mismatch

            else
            {
                int top = alignment_matrix[i-1][j];
                int diagonal = alignment_matrix[i-1][j-1];
                int left = alignment_matrix[i][j-1];
                
                if(top > diagonal)
                {
                    if(top > left)
                    {
                        alignment_matrix[i][j] = top - 1;
                        row[i][j] = i-1;
                        column[i][j] = j;
                    }
                    else
                    {
                        alignment_matrix[i][j] = left - 1;
                        row[i][j] = i;
                        column[i][j] = j-1;
                    }
                }
                else if(diagonal > left)
                {
                    alignment_matrix[i][j] = diagonal - 1;
                    row[i][j] = i-1;
                    column[i][j] = j-1;
                }
                else
                {
                    alignment_matrix[i][j] = left - 1;
                    row[i][j] = i;
                    column[i][j] = j-1;
                }
            }
        }
    }

    int largest = -100;     //To find the greatest element in the matrix
    
    int largest_row_idx = 0; //To store the row no of the largest value
    int largest_col_idx = 0; // To store the column no of the largest value
    
    // Printing the alignment matrix
    cout <<"\nAlignment Matrix\n\n";
    for(int i =0; i < offspring.length()+1; i++)
    {
        for(int j = 0; j < parent.length()+1; j++)
        {
            cout <<alignment_matrix[i][j]<<" ";
             // To find the largest element
            if(alignment_matrix[i][j] > largest)
            {
                largest = alignment_matrix[i][j];
                largest_row_idx = i;
                largest_col_idx = j;
            }
        }
        cout<<"\n";
    }
    
    int i = largest_row_idx;
    int j = largest_col_idx;
    
    int arrow_count = 0;
    // Performing backtracking
    cout<<"\nBacktracking:\n";
    while(i!= 0 && j != 0)
    {
        cout<<alignment_matrix[i][j];
        if(row[i][j]!= 0 && column[i][j]!= 0)
        {
            cout<<"->";
            arrow_count += 1;
        }
        
        int i1 = row[i][j];
        int j1 = column[i][j];
        
        i = i1;
        j = j1; 
    }
    
    int counter = 0;
    
    i = largest_row_idx;
    j = largest_col_idx;
    
    string new_off1 = "";
    string new_off2 = "";
    
    while(counter!=arrow_count)
    {
        // In case of a match
        if(parent[j-1] == offspring[i-1])
        {
            new_off1 = parent[j-1]+new_off1;
            new_off2 = offspring[i-1]+new_off2;
            counter += 1;
        }
        //In case of a mismatch
        else
        {
            //In case of insertion
            if(j = column[i][j])
            {
              new_off1 = '_'+new_off1;
              new_off2 = offspring[i-1]+new_off2;
            }
            //In case of deletion
            else
            {
             new_off1 = parent[j-1]+new_off1;
             new_off2 = '_'+new_off2;
            }
            counter += 1;
        }
        
        int i1 = row[i][j];
        int j1 = column[i][j];
        
        i = i1;
        j = j1; 
    }
    
    //In case of 1st letter match
    if(offspring[0] == parent[0])
    {
        new_off1 = parent[0]+new_off1;
        new_off2 = offspring[0]+new_off2;
    }
    
    //In case of 1st letter mismatch
    else
    {
        new_off1 = '_'+new_off1;
        new_off2 = '_'+new_off2;
    }
    
    //Printing the alignment result
    cout<<"\n\nAlignment Result:\n";
    cout<<"New Offspring 1: "<<new_off1<<"\n";
    cout<<"New Offspring 2: "<<new_off2<<"\n";
    return 0;
}

// IT IS NOT POSSIBLE TO USE PRIM'S AND KRUSKAL'S HERE 