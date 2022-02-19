#include "Edge.h"

Edge::Edge() { u = v = w = next = 0; }

Edge::Edge(int u, int v, int w, int next): u(u), v(v), w(w), next(next) {}
