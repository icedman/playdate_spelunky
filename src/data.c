#include "data.h"
#include "context.h"
#include "game.h"

void PlayerOnEnter(entity_t *t);
void PlayerOnUpdate(entity_t *t, float dt);
void PushBlockOnEnter(entity_t *t);
void PushBlockOnUpdate(entity_t *t, float dt);
void SnakeOnEnter(entity_t *t);
void SnakeOnUpdate(entity_t *t, float dt);
void BatOnEnter(entity_t *t);
void BatOnUpdate(entity_t *t, float dt);
void SpiderOnEnter(entity_t *t);
void SpiderOnUpdate(entity_t *t, float dt);
void SpiderHangOnUpdate(entity_t *t, float dt);
void SpiderHangOnRender(entity_t *t, context_t *context);
void WhipOnEnter(entity_t *t);
void WhipOnUpdate(entity_t *t, float dt);

// clang-format off
static objectDefinition_t defs[] = {
  {EMPTY_SPACE, NULL, NULL, NULL, NULL},
  {PUSH_BLOCK, PushBlockOnEnter, NULL, PushBlockOnUpdate, NULL},
  {GOLD_IDOL, NULL, NULL, NULL, NULL},
  {ALTAR_LEFT, NULL, NULL, NULL, NULL},
  {ALTAR_RIGHT, NULL, NULL, NULL, NULL},
  {SAC_ALTAR_LEFT, NULL, NULL, NULL, NULL},
  {SAC_ALTAR_RIGHT, NULL, NULL, NULL, NULL},
  {BLOCK, NULL, NULL, NULL, NULL},
  {BRICK, NULL, NULL, NULL, NULL},
  {BRICK_2, NULL, NULL, NULL, NULL},
  {LADDER, NULL, NULL, NULL, NULL},
  {LADDER_TOP, NULL, NULL, NULL, NULL},
  {SPIKES, NULL, NULL, NULL, NULL},
  {ENTRANCE, NULL, NULL, NULL, NULL},
  {EXIT, NULL, NULL, NULL, NULL},
  {PLAYER, PlayerOnEnter, NULL, PlayerOnUpdate, NULL},
  {WHIP, WhipOnEnter, NULL, WhipOnUpdate, NULL},
  {SNAKE, SnakeOnEnter, NULL, SnakeOnUpdate, NULL},
  {BAT, BatOnEnter, NULL, BatOnUpdate, NULL},
  {SPIDER, SpiderOnEnter, NULL, SpiderOnUpdate, NULL},
  {SPIDER_HANG, SpiderOnEnter, NULL, SpiderOnUpdate, NULL},
  // {SPIDER_HANG, SpiderOnEnter, NULL, SpiderHangOnUpdate, SpiderHangOnRender},
  {TYPE_END}
};
// clang-format on

objectDefinition_t *ObjectDefinition(entityType_t t) {
  for (int i = 0;; i++) {
    if (defs[i].type == TYPE_END)
      break;
    if (defs[i].type == t) {
      return &defs[i];
    }
  }
  return NULL;
}

bool AreEntitiesNear(entity_t *entity1, entity_t *entity2) {
  vector_t dist = VectorSubtracted(&entity1->position, &entity2->position);
  int nearDistance = 64;
  return ABS(dist.x) < nearDistance && ABS(dist.y) < nearDistance;
}

bool IsLadderEntity(entity_t *entity) {
  switch (entity->type) {
  case LADDER:
  case LADDER_TOP:
    return true;
  }
  return false;
}

bool IsSolidEntity(entity_t *entity) {
  switch (entity->type) {
  case LADDER:
  case LADDER_TOP:
  case ENTRANCE:
  case EXIT:
    return false;
  }
  return (entity->type > START_BLOCKS && entity->type < END_BLOCKS);
}

bool IsEnemyEntity(entity_t *entity) {
  return (entity->type > START_ENEMIES && entity->type < END_ENEMIES);
}

bool IsBlockEntity(entity_t *entity) {
  return (entity->type > START_BLOCKS && entity->type < END_BLOCKS);
}

bool IsCharacterEntity(entity_t *entity) {
  return (entity->type > START_CHARACTERS && entity->type < END_CHARACTERS);
}

bool IsBrickOrBlock(entity_t *entity) {
  return entity->type == BRICK || entity->type == BLOCK;
}

void EnemyEntityDie(entity_t *entity) {
  entity->renderCollisionBounds = true;
  entity->life = 1.0;
  entity->onEffect = EffectFlicker;
}

void EntityCollideEnvironment(entity_t *t, vector_t *direction) {
  memset(t->col, 0, sizeof(void *) * 4);
  memset(t->collisions, 0, sizeof(void *) * 4);

  game_t *gm = GameInstance();

  float tolerance = 2;

  rect_t tr = RectOffset(t->collisionBounds, t->position);
  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;

    if (!IsSolidEntity(e) || !AreEntitiesNear(e, t) || e == t) {
      continue;
    }

    rect_t r = RectOffset(e->collisionBounds, e->position);
    // left top
    if (RectContains(r, tr.lt)) {
      // e->renderCollisionBounds = true;
      t->lt = e;
    }
    // right top
    if (RectContains(r, tr.rt)) {
      // e->renderCollisionBounds = true;
      t->rt = e;
    }
    // left bottom
    if (RectContains(r, tr.lb)) {
      // e->renderCollisionBounds = true;
      t->lb = e;
    }
    // right bottom
    if (RectContains(r, tr.rb)) {
      // e->renderCollisionBounds = true;
      t->rb = e;
    }
  }

  t->topCollision = t->lt ? t->lt : t->rt;
  t->bottomCollision = t->lb ? t->lb : t->rb;
  t->leftCollision = t->lt ? t->lt : t->lb;
  t->rightCollision = t->rt ? t->rt : t->rb;

  if (t->topCollision) {
    t->topCollision->renderCollisionBounds = true;
    // rect_t r =
    //     RectOffset(t->topCollision->collisionBounds, t->topCollision->position);
    // if (r.lb.y > tr.lt.y && (ABS((r.lb.y - tr.lt.y)) < tolerance)) {
    //   t->position.y = r.lb.y - t->collisionBounds.lt.y;
    // }
  }
  if (t->bottomCollision) {
    t->bottomCollision->renderCollisionBounds = true;
    // rect_t r = RectOffset(t->bottomCollision->collisionBounds,
    //                       t->bottomCollision->position);
    // if (r.lt.y < tr.lb.y && (ABS((r.lt.y - tr.lb.y)) < tolerance)) {
    //   t->position.y = r.lt.y - t->collisionBounds.rb.y;
    // }
  }

  // if (t->lt) {
  //   rect_t r = RectOffset(t->lt->collisionBounds,
  //                         t->lt->position);
  //   if (r.rt.x > tr.lt.x && (ABS((r.rt.x - tr.lt.x)) < tolerance)) {
  //     t->renderCollisionBounds = true;
  //     t->position.x = r.rt.x - t->collisionBounds.lt.x;
  //   }
  // }

  // if (t->rt) {
  //   rect_t r = RectOffset(t->rt->collisionBounds,
  //                         t->rt->position);
  //   if (r.lt.x < tr.rt.x && (ABS((r.lt.x - tr.rt.x)) < tolerance)) {
  //     t->renderCollisionBounds = true;
  //     t->position.x = r.lt.x - t->collisionBounds.rt.x;
  //   }
  // }
}

//   rect_t tr = RectOffset(t->collisionBounds, t->position);
//   vector_t tc = RectCenter(tr);
// void EntityCollideEnvironment(entity_t *t, vector_t *direction) {
//   game_t *gm = GameInstance();

//   rect_t tr = RectOffset(t->collisionBounds, t->position);
//   vector_t tc = RectCenter(tr);

//   memset(t->collisions, 0, sizeof(void *) * 4);

//   vector_t adjust;
//   VectorZero(&adjust);

//   node_t *n = gm->entities->first;
//   while (n) {
//     entity_t *e = n->data;
//     n = n->next;

//     rect_t r = RectOffset(e->collisionBounds, e->position);
//     if (!IsSolidEntity(e) || !AreEntitiesNear(e, t) || e == t) {
//       continue;
//     }

//     if (RectCollide(tr, r)) {
//       float tolerance = 2;
//       // t->renderCollisionBounds = true;
//       // top
//       if (r.lb.y > tr.lt.y && (ABS((r.lb.y - tr.lt.y)) < tolerance)) {
//         // e->renderCollisionBounds = true;
//         t->position.y = r.lb.y - t->collisionBounds.lt.y;
//         t->topCollision = e;

//         // corner
//         // if (direction) {
//         //   if (direction->x < 0) {
//         //     if ((ABS((r.rb.x - tr.lt.x)) < tolerance)) {
//         //       adjust.x = 1;
//         //       // t->topCollision = NULL;
//         //     }
//         //   } else if (direction->x > 0) {
//         //     if ((ABS((r.lb.x - tr.rt.x)) < tolerance)) {
//         //       adjust.x = -1;
//         //       // t->topCollision = NULL;
//         //     }
//         //   }
//         // }
//       }
//       // bottom
//       if (r.lt.y < tr.lb.y && (ABS((r.lt.y - tr.lb.y)) < tolerance)) {
//         // e->renderCollisionBounds = true;
//         t->position.y = r.lt.y - t->collisionBounds.rb.y;
//         t->bottomCollision = e;
//       }

//       tr = RectOffset(t->collisionBounds, t->position);

//       // left
//       if (r.rt.x > tr.lt.x && (ABS((r.rt.x - tr.lt.x)) < tolerance)) {
//         // e->renderCollisionBounds = true;
//         t->position.x = r.rt.x - t->collisionBounds.lt.x;
//         t->leftCollision = e;

//         // corner
//         // if (direction && !t->topCollision) {
//         //   if (direction->x < 0) {
//         //     float d = VectorDistanceTo(&r.rb, &tr.lt);
//         //     if ((ABS((r.rb.y - tr.lt.y)) < tolerance)) {
//         //       t->renderCollisionBounds = true;
//         //       adjust.x -= 2;
//         //       adjust.y = 4;
//         //       t->leftCollision = NULL;
//         //     }
//         //   }
//         // }
//       }
//       // right
//       if (r.lt.x < tr.rt.x && (ABS((r.lt.x - tr.rt.x)) < tolerance)) {
//         // e->renderCollisionBounds = true;
//         t->position.x = r.lt.x - t->collisionBounds.rt.x;
//         t->rightCollision = e;

//         // corner
//         // if (direction && !t->topCollision) {
//         //   if (direction->x > 0) {
//         //     if ((ABS((r.lb.y - tr.rt.y)) < tolerance)) {
//         //       t->renderCollisionBounds = true;
//         //       adjust.x += 2;
//         //       adjust.y = 4;
//         //       t->rightCollision = NULL;
//         //     }
//         //   }
//         // }
//       }
//     }
//   }
//   t->position.x += adjust.x;
//   t->position.y += adjust.y;
// }

entity_t *EntityAtPoint(vector_t pos, list_t *entities,
                        bool (*filter)(entity_t *)) {
  node_t *n = entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (filter && !filter(e)) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (RectContains(r, pos)) {
      return e;
    }
  }
  return NULL;
}