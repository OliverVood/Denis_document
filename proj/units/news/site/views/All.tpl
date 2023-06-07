<?php

	namespace Proj\Site\Templates\News;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

	abstract class All {

		public static function ToVar(array $items, $title): string {
			Buffering::Start();
			self::Render($items, $title);
			return Buffering::Read();
		}

		public static function Render(array $items, $title): void { ?>
			<div class = "view news all">
				<div class = "grid col_1">
					<div>
						<h1><?= $title; ?></h1>
					</div>
				</div>
				<div class = "list grid col_3">
					<?php foreach ($items as $item) self::RenderItem($item); ?>
				</div>
			</div>
		<?php }

		public static function RenderItem(array $item): void {
			$background = $item['cover'] ? 'style = "background-image: url(' . Consts\News::PATH_COVER_RELATIVE . $item['cover'] . ');"' : '';
		?>
			<div class = "view news item">
				<div class = "cover"<?= $background; ?>></div>
				<h3 class = "header"><?= $item['header']; ?></h3>
				<div class = "content"><?= $item['content']; ?></div>
				<div class = "links"><?= Actions\News::$show->GetLinkHref('Читать', ['id' => $item['id']]); ?></div>
			</div>
		<?php }

	}