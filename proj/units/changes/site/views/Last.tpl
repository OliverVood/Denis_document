<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\Template;
	use Proj\Site\Units;

	abstract class Last {

		public static function ToVar(array $items, $title): string {
			Template::Start();
			self::Render($items, $title);
			return Template::Read();
		}

		public static function Render(array $items, $title): void {
			if (!$items) return;
		?>
			<div class = "view changes last_items">
				<div class = "grid col_1">
					<div>
						<h2><?= $title; ?></h2>
					</div>
				</div>
				<div class = "list">
					<?php foreach ($items as $item) self::RenderItem($item); ?>
				</div>
				<div class = "all"><?= Units\Changes::instance()->list->GetLink('Все изменения'); ?></div>
			</div>
		<?php }

		public static function RenderItem(array $item): void { ?>
			<div class = "view changes item">
				<?= Units\Changes::instance()->show->GetLink($item['header'], ['id' => $item['id']]); ?>
			</div>
		<?php }

	}