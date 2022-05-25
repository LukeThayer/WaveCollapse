#include <iostream>
#include <time.h>
#include <vector>




class Sockets
{
public:
    int top;
    int bottom;
    int left;
    int right;

    Sockets(int _top, int _bottom, int _left, int _right);
    Sockets();
    ~Sockets();
};

Sockets::Sockets()
{
    top = -1;
    bottom = -1;
    left = -1;
    right= -1;
}

Sockets::Sockets(int _top, int _bottom, int _left, int _right)
{
    top = _top;
    bottom = _bottom;
    left = _left;
    right= _right;
}

Sockets::~Sockets()
{
}


class Tile
{
    public:
    char texture;
    Sockets sockets;
    std::vector<int> sP;
    bool collapsed = false;


    
    Tile(char _texture, Sockets _sockets, std::vector<int> _sP, bool _collapsed);
    Tile(char _texture, Sockets _sockets);
    ~Tile();
};

Tile::Tile(char _texture, Sockets _sockets, std::vector<int> _sP, bool _collapsed)
{
    texture = _texture;
    sockets = _sockets;
    sP = _sP;
    collapsed = _collapsed;
}

Tile::Tile(char _texture, Sockets _sockets)
{
    texture = _texture;
    sockets = _sockets;
    collapsed = true;
}

Tile::~Tile()
{
}

class Map
{
public:
    // The "map" the number of tiles is n*m
    std::vector<Tile> tiles;

    // a list of all tile types
    std::vector<Tile> tileList;
    // number of tile types
    int tile_count;

    // height of map
    int n;

    // width of map
    int m;


// n - height of map, m - width of map, tileList - tiles to be used
    Map(int _n, int _m, std::vector<Tile> _tileList);
    ~Map();
   void print();
   int get_index(int x, int y);
   int get_y(int index);
   int get_x(int index);
   void updateSurroundingTiles(int index);

   void iterate();
   void generate();
   
};

Map::Map(int _n, int _m, std::vector<Tile> _tileList)
{
    n = _n;
    m = _m;
    tileList = _tileList;
    tile_count = tileList.size();

    tiles.reserve(n*m);

    // initializes the tiles on the map to the defualt state-
    // - all tiles have a superposition of all tile types
    // - all tiles are set to not collapsed
    // - all tiles are given the defualt texture

    Sockets empty(-1,-1,-1,-1);
    std::vector<int> sP;
    sP.reserve(n*m);

    for (int j = 0; j < tile_count; j++)
        {
            sP[j] = j;
        }

    Tile none('X',empty ,sP,false);

    tiles.reserve(n*m);
    for (int i = 0; i < n*m; i++)
    {
        tiles[i] = none;
    }
    

        

}

Map::~Map()
{

}

void Map::print()
{
    int index;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
          index = get_index(j,i);
          printf("%c",tiles[index].texture);

        }
        printf("\n");
        
    }
    

}

int Map::get_index(int x, int y)
{
return y*m+x;
}

int Map::get_y(int index)
{
 return index/m;
}

int Map::get_x(int index)
{
 return index%m;
}

void Map::iterate()
{

}

void Map::updateSurroundingTiles(int index)
{

}
void Map::generate()
{
 srand(time(NULL));
 int index = rand()%(n*m);
 int x = get_x(index);
 int y = get_y(index);

 printf("\n %d \n", index);
 printf("\n x : %d \n y : %d \n",x,y);
 printf ("\nindex : %d \n\n", get_index(x,y));

 Tile *startingTile = &tiles[index];
 *startingTile = tileList[rand()%tile_count];



    // first we check the tile to the right of the newly collapsed tile

    // newsP - this vector will be populated with the new superpositons determined by the collapsed tile
    std::vector<int> newsP;

       // verify that the tile to the right is on the map if not skip it
    if (x+1 > n-1 && !tiles[get_index(x+1,y)].collapsed)
    {
        
        // socketFilter -  the socket that is used to filter out invalid tiles
        int socketFilter = startingTile->sockets.right;

        // iterates through old list of super positions and only adds super positions that pass through the filter
        for (int i = 0; i < tiles[get_index(x+1,y)].sP.size(); i++)
        {
            if (tileList[tiles[get_index(x+1,y)].sP[i]].sockets.left == socketFilter)
            {
                newsP.push_back(tiles[get_index(x+1,y)].sP[i]);
            }
        
        }
        tiles[get_index(x+1,y)].sP = newsP;


        // check if the newly updated tile should just be collapsed
        if (tiles[get_index(x+1,y)].sP.size() == 1)
        {
            tiles[get_index(x+1,y)] = tileList[tiles[get_index(x+1,y)].sP[0]];
        }
        
    }   
}


int main()
{

    // defining the types of tiles that can be used
    // these will be used as templates to assing to tiles on the map
    Sockets socket_VL(1,1,-1,-1);
    Tile tile_VL('|',socket_VL);


    Sockets socket_HL(-1,-1,2,2);
    Tile tile_HL('-',socket_HL);

    Sockets socket_C(1,1,2,2);
    Tile tile_C('+',socket_C);

    Sockets socket_E(-1,-1,-1,-1);
    Tile tile_E(' ',socket_E);

    // list of potential tiles indexed to thier superposituin index
    std::vector<Tile> tileTypes;
    tileTypes.push_back(tile_VL);
    tileTypes.push_back(tile_HL);
    tileTypes.push_back(tile_C);
    tileTypes.push_back(tile_E);

    Map map(10,5,tileTypes);
    map.generate();
    map.print();

    

return(0);
};

