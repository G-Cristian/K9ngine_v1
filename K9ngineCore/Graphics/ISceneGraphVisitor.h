#pragma once

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    class RenderNode;
    class SceneGraph;
    class TransformNode;

    class ISceneGraphVisitor
    {
    public:
      ISceneGraphVisitor(SceneGraph&);
      virtual ~ISceneGraphVisitor();
      virtual void visit(RenderNode&) = 0;
      virtual void visit(TransformNode&) = 0;
    protected:
      SceneGraph& mSceneGraph;
    };
  }
}