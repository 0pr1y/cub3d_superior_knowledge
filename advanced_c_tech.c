/* Double buffer */

//1 Creer image back_buffer
mlx_new_image();

//2 Dessiner dans image 
mlx_pixel_put(); // || donnees image

//3 swap l'image complete vers fenetre
mlx_put_image_to_window();

typedef struct s_data
{
    void	*mlx;
    void	*win;
    void 	*img;      // Notre back buffer
    char	*addr;     // Adresse des données de l'image
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}	t_data;

// Dans la boucle de jeu
void	game_loop(t_data *data)
{
    while (game_is_running)
    {
        // 1. Traiter les entrées
        process_input();
        
        // 2. Mettre à jour l'état du jeu
        update_game();
        
        // 3. Effacer le back buffer (remplir avec une couleur uniforme)
        clear_image(data);
        
        // 4. Dessiner dans le back buffer
        render_frame(data);
        
        // 5. Swapper les buffers (afficher l'image complète)
        mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    }
}

/*
Interet :
- L'utilisateur ne voit pas les colonnes du raycaster
- Permet d'afficher simultanement textures des murs Nord/Sud/Est/Ouest
*/

// ⚠️: Toujours liberer images creees avec mlx_destroy_image();




/* Data Locality */

//(voir fichier explications)

// Pour le raycaster :

/* 1) Map */
// Plutôt que int **map (tableau de pointeurs)
int *map; // Un seul tableau continu
// Accès: map[y * width + x] au lieu de map[y][x]

/* 2) Textures */
unsigned int *texture; // Tableau de pixels (RGBA ou format compatible)
// Un pixel: texture[y * texture_width + x]

/* 3) algo raycasting */
// Calculs organises pour parcourir donnees sequentiellement
