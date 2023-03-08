<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\View;
//	use Proj\Units\Consts\Changes;
	use Proj\Site\Units;

	class All extends View {

		public function ToVar(array $items, $title): string {
			$this->Start();
			$this->Render($items, $title);
			return $this->Read();
		}

		public function Render(array $items, $title): void { ?>
			<div class = "view changes last_items">
				<h1><?= $title; ?></h1>
				<div class = "list">
					<?php foreach ($items as $item) $this->RenderItem($item); ?>
				</div>
			</div>
		<?php }

		public function RenderItem(array $item): void {
//			$background = $item['cover'] ? 'style = "background-image: url(' . News::PATH_COVER_RELATIVE . $item['cover'] . ');"' : '';
		?>
			<div class = "view changes last_item">
<?php //<!--				<div class = "cover"--><?//= $background; ? ><!--></div>--> ?>
				<h3 class = "header"><?= $item['header']; ?></h3>
<!--				<div class = "content">--><?//= $item['content']; ?><!--</div>-->
				<div class = "links"><?= Units\Changes::instance()->show->GetLink('Читать', ['id' => $item['id']]); ?></div>
			</div>
		<?php }

	}