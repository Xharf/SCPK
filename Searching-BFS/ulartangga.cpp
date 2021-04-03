// C++ program to find minimum number of dice throws required to
// reach last cell from first cell of a given snake and ladder
// board
#include <iostream>
#include <queue>
using namespace std;

// An entry in queue used in BFS
struct queueEntry
{
    int v;    // nomor vertex / cell papan
    int dist; // jarak cell ini dari source (dalam langkah dadu)
};

int mv = 0;
int layer[1000]; // node pertama sebuah layer
int mx[1000];    // minimum langkah dadu (rolling dice) ke vertex saat ini
int node_layer[1000][10];
// fungsi ini mengembalikan nilai minimum dari pelemparan dadu yang
// diperlukan untuk mencapai cell terakhir dari cell ke 0 pada permainan
// ular tangga. move[] adalah sebuah array yang berukuran N di mana N
// adalah nomor yang menunjukkan cell pada papan permainan. Jika pada
// cell tersebut tidak ada tangga ataupun ular, maka nilainya adalah -1.
// tapi jika ada, maka cell tersebut akan menyimpan nomor cell dari
// atas kepala tangga ataupun ekor dari ular.
int getMinDiceThrows(int move[], int N)
{
    // graph memiliki N vertice dan masing-masing
    // dari mereka diset unvisited.
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    // Create a queue for BFS
    queue<queueEntry> q;

    // Mark the node 0 as visited and enqueue it.
    visited[0] = true;
    queueEntry s = {0, 0}; // distance of 0't vertex is also 0
    q.push(s);             // Enqueue 0'th vertex

    // Do a BFS starting from vertex at index 0
    queueEntry qe; // A queue entry (qe)
    while (!q.empty())
    {
        qe = q.front();
        int v = qe.v;     // nomor vertex dari queue entry
        mx[mv] = qe.dist; // jumlah langkah
        layer[mv] = v;    // nomor vertex untuk menampilkan prosesnya nanti
        mv++;
        // jika vertex adalah destinasi tujuan
        // maka proses selesai
        if (v == N - 1)
            break;

        // Tapi jika tidak, maka bagian pertama vertex akan didequeue
        // dan adjacent (atau cell number yang terjangkau oleh
        // pelemparan sebuah dadu -- 6 cell)
        // vertice nya akan dienqueue
        q.pop();
        int i = 0;
        for (int j = v + 1; j <= (v + 6) && j < N; ++j)
        {
            node_layer[mv][i] = j;
            i++;
            // If this cell is already visited, then ignore
            if (!visited[j])
            {
                // Otherwise calculate its distance and mark it
                // as visited
                queueEntry a;
                a.dist = (qe.dist + 1);

                visited[j] = true;
                // Check if there a snake or ladder at 'j'
                // then tail of snake or top of ladder
                // become the adjacent of 'i'
                if (move[j] != -1)
                {
                    a.v = move[j];
                }
                else
                {
                    a.v = j;
                }

                q.push(a);
            }
        }
    }

    // Proses akan sampai di sini ketika 'qe' adalah
    // vertex terakhir. proses ini mengembalikan
    // nilai distance pada qe sebagai keluarannya
    return qe.dist;
}

int main()
{
    // pembuatan board
    const int N = 30;
    int moves[N];
    for (int i = 0; i < N; i++)
        moves[i] = -1;

    // Ladders
    moves[4] = 16;
    moves[2] = 21;
    moves[10] = 25;
    moves[19] = 28;

    // Snakes
    moves[25] = 1;
    moves[20] = 7;
    moves[18] = 3;
    moves[15] = 6;

    cout << "\n";
    cout << "ini adalah permainan ular tangga.\n"
         << "Jika cell bernilai -1 artinya tidak ada apapun\n"
         << "nilai > nomor cell menunjukkan lokasi kepala tangga\n"
         << "nilai < nomor cell menunjukkan lokasi ekor ular\n";
    cout << "papan permainan Ular dan tangga :\n";
    for (int i = 5; i > 0; i--)
    {
        cout << "|";
        if (i % 2 == 0)
            for (int j = i * 6; j > i * 6 - 6; j--)
            {
                cout << "\t" << moves[j];
                // cout << "\t" << j;
            }
        else
            for (int j = (i - 1) * 6 + 1; j < i * 6 + 1; j++)
            {
                cout << "\t" << moves[j];
                // cout << "\t" << j;
            }

        cout << "|" << endl;
    }
    cout << "\nurutan nomor papan permainan:\n";
    for (int i = 5; i > 0; i--)
    {
        cout << "|";
        if (i % 2 == 0)
            for (int j = i * 6 - 1; j > i * 6 - 7; j--)
            {
                cout << "\t" << j + 1;
            }
        else
            for (int j = (i - 1) * 6; j < i * 6; j++)
            {
                cout << "\t" << j + 1;
            }

        cout << "|" << endl;
    }
    cout << "Minimum pelemparan dadu: " << getMinDiceThrows(moves, N);

    // di bawah ini adalah prosesnya
    // bagian ini tidak bukanlah bagian pentingya
    // tapi bagian ini cukup menjelaskan bagaimana
    // program ini berjalan
    cout << "\n\nProses pencarian ";
    cout << "\nmin dadu | first node layer";
    for (int i = 1; i < 100 && mx[i] != 0; i++)
    {
        cout << endl
             << mx[i] << "\t | \t" << layer[i];
    }
    cout << "\nlayer: ";
    int count = 0;
    while (layer[count + 1] != 0)
    {
        count++;
    }
    cout << count;

    cout << "\n\nnode yang dikunjungi setiap layernya:\n";
    for (int i = 1; layer[i] != 0; i++)
    {
        cout << layer[i - 1] << "\t| ";
        for (int j = 0; j < 6 && node_layer[i][j] != 0; j++)
        {
            cout << node_layer[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
    system("pause");
    return 0;
}
