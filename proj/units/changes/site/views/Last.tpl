<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\View;
//	use Proj\Units\Consts\Changes;
	use Proj\Site\Units;

	class Last extends View {

		public function ToVar(array $items, $title): string {
			$this->Start();
			$this->Render($items, $title);
			return $this->Read();
		}

		public function Render(array $items, $title): void {
			if (!$items) return;
		?>
			<div class = "view changes last_items">
				<div class = "grid col_1">
					<div>
						<h2><?= $title; ?></h2>
					</div>
				</div>
				<div class = "list">
					<?php foreach ($items as $item) $this->RenderItem($item); ?>
					<?php foreach ($items as $item) $this->RenderItem($item); ?>
				</div>
				<div class = "all"><?= Units\Changes::instance()->list->GetLink('Все изменения'); ?></div>
			</div>
		<?php }

		public function RenderItem(array $item): void { ?>
			<div class = "view changes last_item">
				<?= Units\Changes::instance()->show->GetLink($item['header'], ['id' => $item['id']]); ?>
			</div>
		<?php }

	}