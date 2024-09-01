#include "entity.h"
#include "renderer.h"

void EntityInit(entity_t *entity) { memset(entity, 0, sizeof(entity_t)); }

void EntityUpdate(entity_t *e, float dt) {
  vector_t a = VectorScaled(&e->acceleration, dt);
  e->velocity = VectorAdded(&e->velocity, &a);

  float l = VectorLength(&e->velocity);
  if (l > e->speed) {
    VectorNormalize(&e->velocity);
    e->velocity = VectorScaled(&e->velocity, e->speed);
  }

  vector_t m = VectorScaled(&e->velocity, dt);
  e->position = VectorAdded(&e->position, &m);
  if (e->life > 0) {
    e->life -= dt;
    if (e->life <= 0) {
      e->life = -1;
    }
  }
}

void EntitiesUpdate(list_t *entityList, float dt) {
  node_t *n = entityList->first;
  while (n) {
    entity_t *e = (entity_t *)n->data;
    entity_impl_t *ei = (entity_impl_t *)e;
    e->frame += e->frameSpeed * dt;
    if (!e->entered && ei->onEnter) {
      ei->onEnter(e);
      e->entered = true;
    }
    e->ticks += dt;
    if (ei->onUpdate) {
      ei->onUpdate(e, dt);
    } else {
      EntityUpdate(e, dt);
    }
    // effects
    if (ei->onEffect) {
      ei->onEffect(e, dt);
    }
    if (e->life == -1) {
      node_t *rm = n;
      n = (void*)n->next;
      if (e->entered && ei->onExit) {
        ei->onExit(e);
        e->entered = false;
      }
      ListRemove(entityList, rm);
      continue;
    }
    n = (void*)n->next;
  }
}

void EntitiesCreateParticles(list_t *entityList, vector_t position, int count,
                             float speed) {
  for (int i = 0; i < count; i++) {
    vector_t v;
    VectorFromAngle(&v, Rand(0, 360));
    VectorNormalize(&v);
    v = VectorScaled(&v, 0.02 + 0.01 * Rnd());
    float xx = position.x + v.x;
    float yy = position.y + v.y;
    vector_t d;
    VectorInit(&d, xx, yy, 0);
    vector_t xy;
    VectorCopy(&xy, &position);
    d = VectorSubtracted(&d, &xy);
    VectorNormalize(&d);

    entity_t *p = tx_malloc(sizeof(entity_t));
    EntityInit(p);
    p->position = xy;
    p->direction = d;
    p->velocity = VectorScaled(&p->direction, speed + 0.35 * Rnd());
    p->life = 1.5;
    p->type = 0;
    ((entity_impl_t *)p)->onRender = RenderParticle;
    ListAppend(entityList, NodeCreate(p, true));
  }
}

void UpdateExplosion(entity_t *entity, float dt) {
  entity->radius += 2.0 * dt;
  VectorFromAngle(&entity->direction, (entity->radius * 0.25 * 360));
}

void EntitiesCreateExplosion(list_t *entityList, vector_t position) {
  entity_t *p = tx_malloc(sizeof(entity_t));
  EntityInit(p);
  p->position = position;
  VectorZero(&p->direction);
  VectorZero(&p->velocity);
  p->life = 0.8;
  p->type = 0;
  ((entity_impl_t *)p)->onUpdate = UpdateExplosion;
  ((entity_impl_t *)p)->onRender = RenderExplosion;
  ListAppend(entityList, NodeCreate(p, true));
}

void EntitiesCreateFloatingText(list_t *entityList, char *text,
                                vector_t position) {
  entity_t *p = tx_malloc(sizeof(entity_t));
  EntityInit(p);
  p->position = position;
  VectorInit(&p->direction, 0, -1, 0);
  VectorNormalize(&p->direction);
  p->velocity = VectorScaled(&p->direction, 0.5);
  p->life = 1.8;
  p->type = 0;
  ((entity_impl_t *)p)->onRender = RenderFloatingText;
  p->data = text;
  ListAppend(entityList, NodeCreate(p, true));
}

void EffectFlicker(entity_t *e, float delta_time) {
  int f = (int)(e->ticks * 100) % 5;
  if (f == 0) {
    e->invisible = !e->invisible;
  }
  if (e->effectTime > 0) {
    e->effectTime -= delta_time;
    if (e->effectTime <= 0) {
      e->effectTime = 0;
      ((entity_impl_t *)e)->onEffect = NULL;
      e->invisible = false;
    }
  }
}