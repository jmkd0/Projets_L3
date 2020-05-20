#To execute 
#python -m pysc2.bin.agent --map FindAndDefeatZerglings
#python -m pysc2.bin.agent --map FindAndDefeatZerglings --agent defeat_agent_hit_run.AutomateHitRun --max_episodes=10 --use_feature_units

"""Scripted agents."""
from pysc2.agents import base_agent
from pysc2.lib import actions
from pysc2.lib import features
from pysc2.lib import units

import math
import random
import numpy as np


class AutomateHitRun(base_agent.BaseAgent):
    scores = []
    run_hit = [0,0]
    size = [5, 75]
    state = 0
    target = [-1, -1]
    target_camera = [-1, -1]
    moves_screen = [[size[0],size[0]], [size[1],size[1]], [size[1],size[0]], [size[0],size[1]]]
    moves = []

    def setup(self, obs_spec, action_spec):
        super(AutomateHitRun, self).setup(obs_spec, action_spec)
        if "feature_units" not in obs_spec:
            raise Exception("This agent requires the feature_units observation.")
        

    def reset(self):
        super(AutomateHitRun, self).reset()
        self.scores.append(0)
        self.state = 0
        self.target = [-1, -1]
        
        self.target_camera = [-1, -1]

    def step(self, obs):
        super(AutomateHitRun, self).step(obs)
        self.scores[self.episodes-1] = obs.observation["score_cumulative"][0]
        #print(self.episodes)
        marines = [[unit.x, unit.y] for unit in obs.observation.feature_units if unit.alliance == features.PlayerRelative.SELF]
        #Si il n'y en a pas
        if len(marines) == 0:
            #On ne fait rien
            return actions.FUNCTIONS.no_op()
        #Sinon
        #Comme les unites seront groupes on generalise leurs coordonnees au marines 0
        
        x = np.sum(np.array(marines)[:,0])/len(marines)
        y = np.sum(np.array(marines)[:,1])/len(marines)
        marine_mean = [x,y]

        # Selection
        if self.state == 0:
            if actions.FUNCTIONS.select_army.id in obs.observation["available_actions"]:
                self.state = 1
                return actions.FUNCTIONS.select_army("select")

        # Attaque
        if self.state == 1:
            if actions.FUNCTIONS.Attack_screen.id in obs.observation["available_actions"]:
                #On recupere les coordonnees des ennemies
                zerglings = [[unit.x, unit.y] for unit in obs.observation.feature_units if unit.alliance == features.PlayerRelative.ENEMY]
                enemys = []
                #On trie les ennemies en enlevant ce qui ne sont pas dans le screen
                for z in zerglings:
                    if z[0] > 0 and z[1] > 0 and z[0] < 80 and z[1] < 80:
                        enemys.append(z)
                #Si il y a au moins un ennemie
                if len(enemys) != 0:
                    self.state = 1
                    #On recupere l'ennemie le plus proche
                    dist = self.distance_enemy (marine_mean, enemys)
                    near = enemys[dist.index(min(dist))]
                    self.target = [-1, -1]
                    #HIT AND RUN
                    if dist < 19.7:
                        self.state = 2
                        return actions.FUNCTIONS.Move_screen("now", self.run_hit)
                    #On l'attaque
                    return actions.FUNCTIONS.Attack_screen("now", near)
                #Si il n'y a pas d'ennemie
                else:
                    #Au prochain step, on va faire bouger nos unites
                    self.state = 2

        # Mouvement
        if self.state == 2:
            #On determine si nos unites on atteint leur cible
            onTarget = self.checkPosition(marine_mean)
            #Si oui
            if onTarget:
                #Au prochain step, on va bouger la camera
                self.state = 3
            #Sinon
            if not onTarget:
                #Au prochain step, on va attaquer
                self.state = 1
            #Si il n'y a pas encore de cible definit
            if self.target == [-1, -1]:
                x,y = self.moves_screen[self.chooserMove()]

                #On definit les coordonnees de la camera en fonction des coordonees de la cible
                if x == self.size[0]:
                    self.target_camera[0] = 0
                if x == self.size[1]:
                    self.target_camera[0] = 63
                if y == self.size[0]:
                    self.target_camera[1] = 32
                if y == self.size[1]:
                    self.target_camera[1] = 39

                self.target = [x, y]
                return actions.FUNCTIONS.Move_screen("now", self.target)

        # Camera
        if self.state == 3:
            self.state = 1
            self.target = [-1, -1]
            return actions.FUNCTIONS.move_camera(self.target_camera)
        return actions.FUNCTIONS.no_op()

        #Test au passage de l etat 2 a 3
    def checkPosition (self, marine_mean):
        dist = math.hypot(marine_mean[0]-self.target[0], marine_mean[1]- self.target[1])
        if dist >  20:
            return False
        else:
            return True
        #Calcule de la distance des marines aux zerglings
    def distance_enemy (self, marine_mean, enemys):
        distance = []
        for enemy in enemys:
            distance.append(math.hypot(marine_mean[0]-enemy[0], marine_mean[1]- enemy[1]))
        return distance
        #On genere un tableau de 4 valeur au maximum de valeurs distincts pour eviter les repetitions
        #Des que le tableau est plein il est a vider les valeurs constituent le cote de mouvement du screen
    def chooserMove(self):
        choice = random.randint(0,3)
        while choice in self.moves:
            choice = random.randint(0,3)
        if len(self.moves) < 4:
            self.moves.append(choice)
        choose = self.moves[-1]
        if len(self.moves) == 4:
            self.moves[:] = []
        return choose

    def __del__(self):
        print("Le score cumulative fait:")
        print(self.scores)
        print("La moyenne est :")
        print(np.mean(self.scores))
        print("L'ecart type est :")
        print(np.std(self.scores))



