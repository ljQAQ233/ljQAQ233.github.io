import os
import yaml

DOCS_DIR = 'docs'
EXTERN_DIR = os.path.join(DOCS_DIR, 'extern')

with open('mkdocs.yml', 'r') as f:
    data = yaml.safe_load(f)

def docs_join(node, parts):
    comps = parts.split(os.sep)[1:]
    for comp in comps[:-1]:
        for item in node:
            if isinstance(item, dict) and comp in item:
                node = item[comp]
                break
        else:
            sub = {comp: []}
            node.append(sub)
            node = sub[comp]
    node.append(parts)

nav = [item for item in data['nav'] if not (isinstance(item, dict) and '外部文档' in item)]

docs = []
for root, dirs, files in os.walk(EXTERN_DIR):
    for filename in sorted(files):
        if filename.endswith('.md'):
            path = os.path.join(root, filename)
            print(f"find {path}")
            docs_join(docs, os.path.relpath(path, DOCS_DIR))

nav.append({'外部文档': docs})
data['nav'] = nav

with open('mkdocs.yml', 'w') as f:
    yaml.dump(data, f, allow_unicode=True, sort_keys=False, default_flow_style=False)
