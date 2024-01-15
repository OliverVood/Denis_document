<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\Buffering;
	use Proj\Site\Actions;

	abstract class All {

		public static function ToVar(array $items, $title): string {
			Buffering::Start();
			self::Render($items, $title);
			return Buffering::Read();
		}

		public static function Render(array $items, $title): void { ?>
			<div class = "view changes all">
				<div class = "grid col_1">
					<div>
						<h1><?= $title; ?></h1>
					</div>
				</div>
				<div class = "list">
					<?php foreach ($items as $item) self::RenderItem($item); ?>
				</div>
			</div>
		<?php }

		public static function RenderItem(array $item): void { ?>
			<div class = "view changes item">
				<?= Actions\Pages::$changes_show->GetLinkHref($item['header'], ['id' => $item['id']]); ?>
			</div>
		<?php }

	}