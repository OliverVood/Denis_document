<?php

	namespace Proj\Site\Templates\News;

	use Base\Templates\View;
	use Proj\Units\Consts\News;
	use Proj\Site\Units;

	class All extends View {

		public function ToVar(array $items, $title): string {
			$this->Start();
			$this->Render($items, $title);
			return $this->Read();
		}

		public function Render(array $items, $title): void { ?>
			<div class = "view news all">
				<div class = "grid col_1">
					<div>
						<h1><?= $title; ?></h1>
					</div>
				</div>
				<div class = "list grid col_3">
					<?php foreach ($items as $item) $this->RenderItem($item); ?>
				</div>
			</div>
		<?php }

		public function RenderItem(array $item): void {
			$background = $item['cover'] ? 'style = "background-image: url(' . News::PATH_COVER_RELATIVE . $item['cover'] . ');"' : '';
		?>
			<div class = "view news item">
				<div class = "cover"<?= $background; ?>></div>
				<h3 class = "header"><?= $item['header']; ?></h3>
				<div class = "content"><?= $item['content']; ?></div>
				<div class = "links"><?= Units\News::instance()->show->GetLink('Читать', ['id' => $item['id']]); ?></div>
			</div>
		<?php }

	}