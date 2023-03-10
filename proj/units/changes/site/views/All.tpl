<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\View;
	use Proj\Site\Units;

	class All extends View {

		public function ToVar(array $items, $title): string {
			$this->Start();
			$this->Render($items, $title);
			return $this->Read();
		}

		public function Render(array $items, $title): void { ?>
			<div class = "view changes all">
				<div class = "grid col_1">
					<div>
						<h1><?= $title; ?></h1>
					</div>
				</div>
				<div class = "list">
					<?php foreach ($items as $item) $this->RenderItem($item); ?>
				</div>
			</div>
		<?php }

		public function RenderItem(array $item): void { ?>
			<div class = "view changes item">
				<?= Units\Changes::instance()->show->GetLink($item['header'], ['id' => $item['id']]); ?>
			</div>
		<?php }

	}