using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace K9ngine_v1_editor
{
    [Serializable]
    public class Point2D
    {
        public float x;
        public float y;

        public Point2D()
        {
            x = 0.0f;
            y = 0.0f;
        }

        public Point2D(Point2D other)
        {
            x = other.x;
            y = other.y;
        }
    }

    [Serializable]
    public class Point3D
    {
        public float x;
        public float y;
        public float z;

        public Point3D()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        public Point3D(Point3D other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
    }

    [Serializable]
    public class Vec4D
    {
        public float x;
        public float y;
        public float z;
        public float w;

        public Vec4D()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 0.0f;
        }

        public Vec4D(Vec4D other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }
    }

    [Serializable]
    public class Vertex
    {
        public Point3D Position { get; set; }
        public Point3D Normal { get; set; }
        public Point2D TextureCoord { get; set; }
        public Vec4D Color { get; set; }

        public Vertex(float px, float py, float pz, float nx, float ny, float nz, float s, float t, float r, float g, float b, float a)
        {
            Position.x = px;
            Position.y = py;
            Position.z = pz;

            Normal.x = nx;
            Normal.y = ny;
            Normal.z = nz;

            TextureCoord.x = s;
            TextureCoord.y = t;

            Color.x = r;
            Color.y = g;
            Color.z = b;
            Color.w = a;
        }

        public Vertex(Point3D pos, Point3D norm, Point2D texCoord, Vec4D color)
        {
            Position = new Point3D(pos);
            Normal = new Point3D(norm);
            TextureCoord = new Point2D(texCoord);
            Color = new Vec4D(color);
        }
    }

    public abstract class VertexSaver
    {
        public abstract void Save(Action<FileStream, float> saveFloat, FileStream file, Vertex vertex);
    }

    public class VertexSaverPositionNormal: VertexSaver
    {
        public override void Save(Action<FileStream, float> saveFloat, FileStream file, Vertex vertex)
        {
            saveFloat(file, vertex.Position.x);
            saveFloat(file, vertex.Position.y);
            saveFloat(file, vertex.Position.z);

            saveFloat(file, vertex.Normal.x);
            saveFloat(file, vertex.Normal.y);
            saveFloat(file, vertex.Normal.z);
        }
    }

    public class VertexSaverPositionNormalColor : VertexSaverPositionNormal
    {
        public override void Save(Action<FileStream, float> saveFloat, FileStream file, Vertex vertex)
        {
            base.Save(saveFloat, file, vertex);

            saveFloat(file, vertex.Color.x);
            saveFloat(file, vertex.Color.y);
            saveFloat(file, vertex.Color.z);
            saveFloat(file, vertex.Color.w);
        }
    }

    public class VertexSaverPositionNormalTexCoord : VertexSaverPositionNormal
    {
        public override void Save(Action<FileStream, float> saveFloat, FileStream file, Vertex vertex)
        {
            base.Save(saveFloat, file, vertex);

            saveFloat(file, vertex.TextureCoord.x);
            saveFloat(file, vertex.TextureCoord.y);
        }
    }

    public class VertexSaverPositionNormalTexCoordColor : VertexSaverPositionNormal
    {
        public override void Save(Action<FileStream, float> saveFloat, FileStream file, Vertex vertex)
        {
            base.Save(saveFloat, file, vertex);

            saveFloat(file, vertex.TextureCoord.x);
            saveFloat(file, vertex.TextureCoord.y);

            saveFloat(file, vertex.Color.x);
            saveFloat(file, vertex.Color.y);
            saveFloat(file, vertex.Color.z);
            saveFloat(file, vertex.Color.w);
        }
    }

    [Serializable]
    public class Mesh:BaseAsset
    {
        public enum VerticesTypeEnum { PositionNormal, PositionNormalColor, PositionNormalTexCoord, PositionNormalTexCoordColor }

        public VerticesTypeEnum VerticesType { get; set; }

        public List<Vertex> Vertices { get; set; }
        public List<int> Indices { get; set; }

        public Mesh() : base()
        {
            Vertices = new List<Vertex>();
            Indices = new List<int>();
        }

        public void AddVertex(Vertex vertex)
        {
            Vertices.Add(vertex);
        }

        public void AddIndex(int index)
        {
            Indices.Add(index);
        }
    }
}
