import { defineShikiSetup } from '@slidev/types'

export default defineShikiSetup(() => ({
  transformers: [
    {
      line(node) {
        const text = node.children
          ?.map((c: any) => c.children?.map((s: any) => s.value ?? '').join('') ?? c.value ?? '')
          .join('') ?? ''
        if (!node.properties) node.properties = {}
        if (text.startsWith('+ ')) node.properties.class = 'line diff-add'
        else if (text.startsWith('- ')) node.properties.class = 'line diff-remove'
      },
    },
  ],
}))

