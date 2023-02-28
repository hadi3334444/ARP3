#include "./../include/processB_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <bmpfile.h>
#include <fcntl.h>
#include <sys/mman.h>
const int SIZE = 1600*600*sizeof(int);
bmpfile_t *bmap;
//shared memory object
const char* name = "shm";
//file descriptor
int fd;
//shared memory object pointer
int* ptr;
int i_center;
int j_center;

void find_center(){
    int i_min = 1600;
    int i_max = 0;
    int j_min = 600;
    int j_max = 0;
    for (int i = 0; i < 1600; i++) {
        for (int j = 0; j < 600; j++) {
            rgb_pixel_t *pixel = bmp_get_pixel(bmap, i, j);
            if (pixel->red == 100) {
                //i_min = i_min < i ? i_min : i;
                //i_max = i_max > i ? i_max : i;
                //j_min = j_min < j ? j_min : j;
                //j_max = j_max > j ? j_max : j;
                if(i<i_min) 
                    i_min=i;
                if(i>i_max)
                    i_max=i;
                if(j<j_min)
                    j_min=j;
                if(j>j_max)
                    j_max=j;
            }
        }
    }
    i_center = (i_min + i_max) / 2;
    j_center = (j_min + j_max) / 2;
    i_center /= (1600 / COLS);
    j_center /= (600 / LINES);
    mvprintw(LINES - 1, 1, "loc of i is : %d", i_center);
    mvprintw(LINES - 2, 1, "loc of j is : %d", j_center);
    mvaddch(j_center, i_center, '0');
    refresh();
}

void load_shared_memory(){
    bmap = bmp_create(1600, 600, 4);
    for(int i = 0; i < 1600; i++)
    {
        for(int j = 0; j < 600; j++)
        {
            if (ptr[i*599+j]==100)
            {
                rgb_pixel_t pixel = {0, 0, ptr[i*599+j], 0};
                bmp_set_pixel(bmap,i,j, pixel);
            }
            else{
                rgb_pixel_t pixel = {255, 255, 255, 0};
                bmp_set_pixel(bmap,i,j, pixel);
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    //sleep(1);
    //Open shared memory as ReadOnly 
    fd = shm_open(name, O_RDONLY, 0666);
    //Memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;
    // Initialize UI
    init_console_ui();
    // Infinite loop
    while (TRUE) {
        // Get input in non-blocking mode
        int cmd = getch();
        // If user resizes screen, re-draw UI...
        if(cmd == KEY_RESIZE) {
            if(first_resize) {
                first_resize = FALSE;
            }
            else {
                reset_console_ui();
            }
        }
        else {
		load_shared_memory();
		find_center();
		bmp_destroy(bmap);
        }
    }
    endwin();
    return 0;
}





