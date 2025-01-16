english = (
    "Don't wait, father, I said. "
    "He looked out of the window. "
    "I'll just buy you a few tangerines, he said. Wait here, and don't wander off. "
    "Just outside the station were some vendors. To reach them he had to cross the lines, "
    "which involved jumping down from the platform and clambering up again. "
    "As my father is a stout man, this was naturally not easy for him. "
    "But when I volunteered to go instead, he would not hear of it. "
    "So I watched him in his black cloth cap and jacket and dark blue cotton-padded gown, "
    "as he waddled to the tracks and climbed slowly down—not so difficult after all. "
    "But when he had crossed the lines, he had trouble clambering up the other side. "
    "He clutched the platform with both hands and tried to heave his legs up, straining to the left. "
    "At the sight of his burly back, tears started to my eyes, but I wiped them hastily so that neither he "
    "nor anyone else might see them. "
    "When next I looked out, he was on his way back with some ruddy tangerines. "
    "He put these on the platform before climbing slowly down to cross the lines, "
    "which he did after picking the fruit up. "
    "When he reached my side, I was there to help him up. "
    "We boarded the train together, and he plumped the tangerines down on my coat. "
    "Then he brushed the dust from his clothes, as if that was a weight off his mind. "
    "I'll be going now, son, he said presently. Write to me once you get there. "
    "I watched him walk away. After a few steps, he turned back to look at me. "
    "Go on in! he called. There's no one in the compartment. "
    "When his back disappeared among the bustling crowd, I went in and sat down, "
    "and my eyes were wet again."
)

chinese = (
    "我说道，“爸爸，你走吧。”他往车外看了看，说，“我买几个橘子去。你就在此地，不要走动。”"
    "我看那边月台的栅栏外有几个卖东西的等着顾客。走到那边月台，须穿过铁道，须跳下去又爬上去。"
    "父亲是一个胖子，走过去自然要费事些。我本来要去的，他不肯，只好让他去。"
    "我看见他戴着黑布小帽，穿着黑布大马褂，深青布棉袍，蹒跚地走到铁道边，慢慢探身下去，尚不大难。"
    "可是他穿过铁道，要爬上那边月台，就不容易了。他用两手攀着上面，两脚再向上缩；"
    "他肥胖的身子向左微倾，显出努力的样子。这时我看见他的背影，我的泪很快地流下来了。"
    "我赶紧拭干了泪，怕他看见，也怕别人看见。我再向外看时，他已抱了朱红的桔子往回走了。"
    "过铁道时，他先将桔子散放在地上，自己慢慢爬下，再抱起桔子走。到这边时，我赶紧去搀他。"
    "他和我走到车上，将桔子一股脑儿放在我的皮大衣上。于是扑扑衣上的泥土，心里很轻松似的。"
    "过一会儿说，“我走了，到那边来信！”我望着他走出去。他走了几步，回过头看见我，说，“进去吧，里边没人。”"
    "等他的背影混入来来往往的人里，再找不着了，我便进来坐下，我的眼泪又来了。"
)

# print(len(english) / 16)
# print(len(chinese) / 4)

chinese_group_n = 4
english_group_n = len(english) // (len(chinese) // chinese_group_n)

english_groups = [english[i : i + english_group_n] for i in range(0, len(english), english_group_n)]
chinese_groups = [chinese[i : i + chinese_group_n] for i in range(0, len(chinese), chinese_group_n)]

# print(len(english_groups))
# print(len(chinese_groups))

# chinese_groups += [""]

merged = zip(chinese_groups, english_groups)

for pair in merged:
    print(pair[0], "\t", pair[1])

# print(len(pair[0]) + len(pair[1]))

