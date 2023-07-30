#include "renderer/irenderer.h"
#include <stdlib.h>

InterfaceRenderer *create_InterfaceRenderer_fn(void (*crtRenderer_fn)(void *self, void *o), void (*draw_fn)(void *self, void *o), void (*dstrRenderer_fn)(void *self))
{
	InterfaceRenderer *irenderer = (InterfaceRenderer *)malloc(sizeof(InterfaceRenderer));
	irenderer->createRenderer_fn = crtRenderer_fn;
	irenderer->draw_fn = draw_fn;
	irenderer->destroyRenderer_fn = dstrRenderer_fn;
	return irenderer;
}

void destroy_InterfaceRenderer_fn(InterfaceRenderer *irenderer);
