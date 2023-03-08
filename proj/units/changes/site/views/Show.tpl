<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\View;
	use Proj\Units\Consts\Changes;

	class Show extends View {

		public function ToVar(array $data, array $list): string {
			$this->Start();
			$this->Render($data, $list);
			return $this->Read();
		}

		public function Render(array $data, array $list): void { ?>
			<div class = "view changes show">
				<h1><?= $data['header']; ?></h1>
				<div class = "list">
					<?php foreach ($list as $item) $this->RenderChange($item); ?>
				</div>
				<div class = "data publish"><?= $data['datepb']; ?></div>
			</div>
		<?php }

		private function RenderChange($item): void {
			$background = $item['cover'] ? 'style = "background-image: url(' . Changes::PATH_COVER_RELATIVE . $item['cover'] . ');"' : '';
		?>
			<div class = "view change item">
				<div class = "cover"<?= $background; ?>></div>
				<div class = "wrap">
					<div class = "header"><?= $item['header']; ?></div>
					<div class = "content"><?= $item['content']; ?></div>
				</div>
			</div>
		<?php }

	}