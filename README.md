# RogueOne
A remake of the classic Rogue RPG game. Was it better or worse?

# Screenshots
![img1](http://res.cloudinary.com/rube0414/image/upload/v1504834764/1_xutfxb.jpg)
![img1](http://res.cloudinary.com/rube0414/image/upload/v1504834764/2_ajqrbk.png)

# Features
## Map Generation
Unlike other trivial implementations using an array, this game map is implemented with an algorithm that allows for virtually unlimited map size and uses O(1) space.
## Collision Detection
Since the map is not stored in an array, collision with room borders and monsters are calculated with an algorithm that runs in O(n)
## Monsters
Monsters are smart. They will follow you around if you are within a certain distance. They will grow stronger as you clear each level and run faster and detect you faster. So run while you can!
## Items
There are two main types of items: health potions and ability items. health potions gives you more HP. Ability items can increase your attack damage, armor etc. Items effects and appearance scale with level.
