from abc import abstractmethod

class Organism :
    
    def __init__(self, species, x, y, strength, initiative, world, can_breed, breed_cooldown) :
        self._species = species
        self._x = x
        self._y = y
        self._age = 0
        self._dead = False
        self._strength = strength
        self._initiative = initiative
        self._world = world
        self._can_breed = can_breed
        self._breed_cooldown = breed_cooldown

        world.set_organism(self, x, y)
        world.add_organism(self)

    @abstractmethod
    def action(self) :
        pass

    @abstractmethod
    def collision(self, other) :
        pass

    @abstractmethod
    def draw(self) :
        pass

    def move_organism(self, new_x, new_y) :
        occupant = self._world.get_organism(new_x, new_y)
        if (occupant) :
            occupant.collision(self)
        else :
            self._world.set_organism(None, self.x, self.y)
            self._x = new_x
            self._y = new_y
            self._world.set_organism(self, self.x, self.y)

    @property
    def y(self) :
        return self._y

    @property
    def x(self) :
        return self._x
    
    @property
    def strength(self) :
        return self._strength
    
    @property
    def initiative(self) :
        return self._initiative
    
    @property
    def age(self) :
        return self._age
    
    @property
    def species(self) :
        return self._species
    
    def increment_age(self) :
        self._age+=1

    def increment_strength(self, number) :
        self._strength += number

    def is_dead(self) :
        return self._dead
    
    def mark_dead(self) :
        self._dead = True

    def check_can_breed(self) :
        return self._can_breed
    
    def set_breed_cooldown(self) :
        self._breed_cooldown = 3
        self._can_breed = False
        

