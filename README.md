# c++ CG Game

Classic roguelike in gachi dungeon. Try to survive and complete three unique levels filled with monsters and traps.

## Gameplay aspects
- Turn based gameplay
- WASD for movement and attack
- Lure enemies into traps to damage them, but avoid stepping into one
- Enemies will attack you if you step in tile adjacent to them, so keep the distance
- Due to your ethical beliefs you can't go on tiles with enemies' graves, so try not to block your way
- You have 30 hp at the start of each level and no way of restoring it, try not to die :)

## Graphical aspects
- Реализовано 6 видов врагов с разными характеристиками. Если враг не видит игрока, он передвигается в случайном порядке, избегая ловушек;
 если игрок находится в зоне видимости, враг будет идти в его сторону
- Плавная спрайтовая анимация динамических объектов (персонаж и враги)
- Анимация статических объектов (ловушки)
- Графический эффект перехода между уровнями - постепенное “угасание” и появление игровой карты (fade out / fade in)
- <img src="https://github.com/sver-hub/c---CG-Game/blob/master/fadeout.gif" width="400" height="400" />
- Источники света - факелы, которые “освещают” (=изменяют цвет) соседних тайлов в некотором радиусе + анимация источников света
- <img src="https://github.com/sver-hub/c---CG-Game/blob/master/light.gif" width="400" height="400" />
- Графическое отображение характеристик игрока и врагов (здровье)
- Механика ближнего боя с анимацией (у каждого врага собственная анимация атаки)
- <img src="https://github.com/sver-hub/c---CG-Game/blob/master/attack.gif" width="400" height="400" />
- Визуальные эффекты боя - при получении урона спрайт игрока или врага краснеет, анимация смерти
- Карта уровня больше чем отображаемая в окне область, реализовано отображение видимой области, которая располагается вокруг игрока и перемещается вместе с ним
