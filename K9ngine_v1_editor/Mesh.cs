using System;
using System.Collections.Generic;
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
    public class Vertex
    {
        public Point3D Position { get; set; }
        public Point3D Normal { get; set; }
        public Point2D TextureCoord { get; set; }

        public Vertex(float px, float py, float pz, float nx, float ny, float nz, float u, float t)
        {
            Position.x = px;
            Position.y = py;
            Position.z = pz;

            Normal.x = nx;
            Normal.y = ny;
            Normal.z = nz;

            TextureCoord.x = u;
            TextureCoord.y = t;
        }

        public Vertex(Point3D pos, Point3D norm, Point2D texCoord)
        {
            Position = new Point3D(pos);
            Normal = new Point3D(norm);
            TextureCoord = new Point2D(texCoord);
        }
    }

    [Serializable]
    public class Mesh:BaseAsset
    {
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
