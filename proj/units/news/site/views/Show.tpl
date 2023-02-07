<?php

	namespace Proj\Site\Templates\News;

	use Base\Templates\View;
	use Proj\Units\Consts\News;

	class Show extends View {

		public function ToVar(array $data): string {
			$this->Start();
			$this->Render($data);
			return $this->Read();
		}

		public function Render(array $data) {
			$background = $data['cover'] ? 'style = "background-image: url(' . News::PATH_COVER_RELATIVE . $data['cover'] . ');"' : '';
		?>
			<div class = "view news show">
				<h1><?= $data['header']; ?></h1>
				<div class = "cover"<?= $background; ?>></div>
				<div class = "content"><?= $data['content']; ?></div>
				<div class = "data publish"><?= $data['datepb']; ?></div>
			</div>
		<?php }

	}