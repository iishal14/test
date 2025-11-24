
struct Contestant
{
    int id;
    int swim;
    int bike;
    int run;
    int totalBikeAndRun;
    int swimStart;
    int swimEnd;
    int totalFinishTime;
};

void merge(Contestant arr[], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Contestant* L = new Contestant[n1];
    Contestant* R = new Contestant[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) 
    {
        if (L[i].totalBikeAndRun >= R[j].totalBikeAndRun) 
        {
            arr[k] = L[i];
            i++;
        } 
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Contestant arr[], int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void findEarlySchedule(Contestant* c, int n)
{
    mergeSort(c, 0, n-1);

    c[0].swimStart=0;
    c[0].swimEnd=c[0].swim;
    c[0].totalFinishTime=c[0].swimEnd+c[0].totalBikeAndRun;

    for(int i=1;i<n;i++)
    {
        c[i].swimStart=c[i-1].swimEnd;
        c[i].swimEnd=c[i].swimStart+c[i].swim;
        c[i].totalFinishTime=c[i].swimEnd+c[i].totalBikeAndRun;
    }

    cout<<"Schedule: \n";
    for(int i=0;i<n;i++)
    {
        cout<<"---Contestant "<<c[i].id<<"---\n";
        cout<<"Swim Start Time: "<<c[i].swimStart<<"\n";
        cout<<"Swim End Time: "<<c[i].swimEnd<<"\n";
        cout<<"Total Bike and Run Time: "<<c[i].totalBikeAndRun<<"\n";
        cout<<"Total Finish Time: "<<c[i].totalFinishTime<<"\n";
    }

    cout<<"Total Event Finish At: "<<c[n-1].totalFinishTime;
}

int main()
{
    int n=0;
    cout<<"Enter number of contestants (n): ";
    cin>>n;

    Contestant* c=new Contestant[n];
    cout<<"Enter contestant details: \n";
    for(int i=0;i<n;i++)
    {
        c[i].id=i+1;
        cout<<"---Contestant "<<i+1<<"---\n";
        cout<<"Swim: ";
        cin>>c[i].swim;
        cout<<"Bike: ";
        cin>>c[i].bike;
        cout<<"Run: ";
        cin>>c[i].run;
        c[i].totalBikeAndRun=c[i].bike+c[i].run;
    }

    findEarlySchedule(c,n);
}