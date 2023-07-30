#ifndef _IRENDERER_H_
#define _IRENDERER_H_

typedef struct irenderer_t InterfaceRenderer;

typedef struct irenderer_t
{
	void (*createRenderer_fn)(void *self, void *o);
	void (*draw_fn)(void *self, void *o);
	void (*destroyRenderer_fn)(void *self);
} InterfaceRenderer;

InterfaceRenderer *create_InterfaceRenderer_fn(void (*crtRenderer_fn)(void *self, void *o), void (*draw_fn)(void *self, void *o), void (*dstrRenderer_fn)(void *self));

void destroy_InterfaceRenderer_fn(InterfaceRenderer *irenderer);

#endif /* _IRENDERER_H_ */
