# Custom HUD — DayZ (Standalone)

Mod HUD côté client pour **DayZ Standalone** (moteur Enfusion). Affiche un panneau discret en bas à droite de l'écran avec 4 barres + pourcentages :

| Stat | Source script |
|---|---|
| Santé | `GetHealth("GlobalHealth", "Health")` |
| Sang | `GetHealth("GlobalHealth", "Blood")` |
| Eau | `GetStatWater().Get()` |
| Nourriture | `GetStatEnergy().Get()` |

Rafraîchissement toutes les 250 ms via `MissionGameplay.OnUpdate` (coût négligeable).
Le HUD se masque automatiquement quand le personnage est mort ou absent.

## Structure

```
CustomHUD/
├── $PREFIX$                        # prefix de packing : "CustomHUD"
├── config.cpp                      # CfgPatches + CfgMods (module 5_Mission)
├── HUD/
│   └── hud_stats.layout            # panneau UI (format Enfusion, pas du XML)
└── scripts/
    └── 5_Mission/
        └── CustomHUD/
            ├── CustomHUD.c         # classe HUD : création widgets + update
            └── MissionGameplay.c   # modded class MissionGameplay (hook)
```

## Packager en PBO

Avec **DayZ Tools → AddonBuilder** :

1. Source : le dossier `CustomHUD` (celui qui contient `config.cpp`).
2. Destination : ex. `P:\Mods\@CustomHUD\Addons`.
3. Options : `-prefix=CustomHUD` (sinon le fichier `$PREFIX$` s'en charge).
4. Resultat : `CustomHUD.pbo` contenant `config.cpp`, `HUD/`, `scripts/`.

Equivalemment avec **pboProject** ou **Workbench** (projet `dayz.gproj`, prefix `CustomHUD`).

## Installation

### Client (test local)
- Copier `@CustomHUD/Addons/CustomHUD.pbo` dans le dossier du jeu.
- Lancer avec : `-mod=@CustomHUD`

### Serveur
- Uploader le PBO dans le dossier `@CustomHUD/Addons` du serveur.
- Ligne de lancement : `-mod=@CustomHUD` (ou `-serverMod=@CustomHUD` : le HUD est purement client, donc `serverMod` suffit ET évite aux joueurs d'avoir à s'abonner au mod).

> Mod 100 % client : aucune ligne à ajouter dans `cfggameplay.json` ni dans les types.xml. Compatible n'importe quelle carte.

## Personnaliser

- **Position / taille / couleurs** : `HUD/hud_stats.layout` (attributs `position`, `size`, `color r g b a` — valeurs 0.0–1.0).
- **Vitesse de rafraîchissement** : `0.25` dans `CustomHUD.c` (`m_UpdateTimer < 0.25`).
- **Revenir au HUD vanilla** : retirer le mod, aucune trace persistante.

## Notes de compatibilité

- Ce mod override `MissionGameplay` via `modded class` — compatible avec les autres mods qui utilisent le même pattern (charge d'ordre gérée par Enfusion).
- Si un autre mod packe aussi un `scriptclass` homonyme, préfixer. Les classes ici (`CustomHUD`) sont déjà préfixées.
- Testé comme pattern standard des mods communautaires ; vérifier la compilation dans Workbench après mise à jour du jeu (l'API des widgets est stable, mais DayZ casse parfois les signatures entre builds).
